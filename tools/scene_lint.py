#!/usr/bin/env python3
"""Lint RTv1 scene/map files.

This is intentionally stricter than scene_parser.py: the parser accepts the
legacy C behavior where unknown lines are skipped, while the linter reports
unknown directives, misplaced fields, missing values, and invalid values.
"""

from __future__ import annotations

import argparse
import sys
from dataclasses import dataclass
from pathlib import Path

from scene_parser import SceneParseError, parse_scene_file


SCENE_KEYS = {"#name": 1, "#window": 2, "#cam": 3}
OBJECT_KEYS = {
    "sphere": {"#radius": 1, "#origin": 3, "#color": 1, "#ref": 1},
    "plan": {"#const": 1, "#origin": 3, "#color": 1, "#ref": 1},
    "cylinder": {"#origin": 3, "#dir": 3, "#const": 1, "#color": 1, "#ref": 1},
    "cone": {"#origin": 3, "#dir": 3, "#const": 1, "#color": 1, "#ref": 1},
    "light": {"#origin": 3, "#color": 1, "#ref": 1},
}
REQUIRED_KEYS = {
    "sphere": {"#radius", "#origin", "#color"},
    "plan": {"#const", "#origin", "#color"},
    "cylinder": {"#origin", "#dir", "#const", "#color"},
    "cone": {"#origin", "#dir", "#const", "#color"},
    "light": {"#origin", "#color"},
}


@dataclass(frozen=True)
class LintIssue:
    path: Path
    line: int
    message: str

    def format(self) -> str:
        return f"{self.path}:{self.line}: {self.message}"


def _is_comment_or_blank(line: str) -> bool:
    stripped = line.strip()
    return not stripped or stripped.startswith(";")


def _is_decorative(line: str) -> bool:
    return line.startswith(":")


def _is_number(value: str) -> bool:
    try:
        float(value)
    except ValueError:
        return False
    return True


def _is_integer(value: str) -> bool:
    try:
        parsed = float(value)
    except ValueError:
        return False
    return parsed.is_integer()


def _is_color(value: str) -> bool:
    if not value.startswith("0x") or len(value) < 3:
        return False
    try:
        int(value[2:], 16)
    except ValueError:
        return False
    return True


def _next_content(lines: list[tuple[int, str]], idx: int) -> tuple[int, str, int] | None:
    while idx < len(lines):
        line_no, raw = lines[idx]
        idx += 1
        if not _is_comment_or_blank(raw):
            return line_no, raw.strip(), idx
    return None


def _consume_values(
    path: Path,
    lines: list[tuple[int, str]],
    idx: int,
    key: str,
    count: int,
    object_type: str | None,
) -> tuple[int, list[LintIssue]]:
    issues: list[LintIssue] = []
    label = f"{object_type} {key}" if object_type else key

    for pos in range(count):
        item = _next_content(lines, idx)
        if item is None:
            issues.append(LintIssue(path, lines[-1][0] if lines else 1, f"{label} missing value {pos + 1}/{count}"))
            return len(lines), issues
        line_no, value, idx = item
        if value.startswith("#"):
            issues.append(LintIssue(path, line_no, f"{label} missing value before {value!r}"))
            idx -= 1
            return idx, issues
        if key == "#color" and not _is_color(value):
            issues.append(LintIssue(path, line_no, f"{label} must be a hexadecimal color like 0xFF7260"))
        elif key in {"#window", "#ref"} and not _is_integer(value):
            issues.append(LintIssue(path, line_no, f"{label} must be an integer"))
        elif key not in {"#name", "#color"} and not _is_number(value):
            issues.append(LintIssue(path, line_no, f"{label} must be a number"))
    return idx, issues


def _skip_until_object_end(lines: list[tuple[int, str]], idx: int) -> int:
    while idx < len(lines):
        _, line = lines[idx]
        if line.strip() in {"#end_object", "##end"}:
            return idx + 1
        idx += 1
    return idx


def _lint_text(path: Path, text: str) -> list[LintIssue]:
    issues: list[LintIssue] = []
    lines = [(idx, line.strip()) for idx, line in enumerate(text.splitlines(), 1)]
    idx = 0
    state = "preamble"
    seen_scene = False
    seen_objects = False
    scene_seen_keys: set[str] = set()
    current_object: str | None = None
    object_seen_keys: set[str] = set()

    while idx < len(lines):
        line_no, line = lines[idx]
        idx += 1
        if _is_comment_or_blank(line):
            continue

        if state == "preamble":
            if line == "##scene":
                seen_scene = True
                state = "scene"
            else:
                continue
            continue

        if state == "scene":
            if line == "#end_env":
                missing = {"#window", "#cam"} - scene_seen_keys
                for key in sorted(missing):
                    issues.append(LintIssue(path, line_no, f"scene missing required {key}"))
                state = "between_sections"
            elif line in SCENE_KEYS:
                scene_seen_keys.add(line)
                idx, value_issues = _consume_values(path, lines, idx, line, SCENE_KEYS[line], None)
                issues.extend(value_issues)
            elif line.startswith("#"):
                issues.append(LintIssue(path, line_no, f"unknown scene directive {line!r}"))
            else:
                issues.append(LintIssue(path, line_no, f"unexpected scene value {line!r}"))
            continue

        if state == "between_sections":
            if line == "##objects":
                seen_objects = True
                state = "objects"
            elif line.startswith("##") and line != "##scene":
                issues.append(LintIssue(path, line_no, f"unexpected section marker {line!r}"))
            elif line.startswith("#"):
                issues.append(LintIssue(path, line_no, f"directive outside section: {line!r}"))
            else:
                issues.append(LintIssue(path, line_no, f"unexpected content outside section: {line!r}"))
            continue

        if state == "objects":
            if line == "##end":
                state = "done"
            elif line == "#type":
                item = _next_content(lines, idx)
                if item is None:
                    issues.append(LintIssue(path, line_no, "missing object type after #type"))
                    idx = len(lines)
                else:
                    type_line_no, object_type, idx = item
                    if object_type not in OBJECT_KEYS:
                        issues.append(LintIssue(path, type_line_no, f"unsupported object type {object_type!r}"))
                    current_object = object_type
                    object_seen_keys = set()
                    state = "object"
            elif _is_decorative(line):
                continue
            elif line == "##type":
                issues.append(LintIssue(path, line_no, "unknown object directive '##type'; did you mean '#type'?"))
                idx = _skip_until_object_end(lines, idx)
            elif line.startswith("#"):
                issues.append(LintIssue(path, line_no, f"object field outside object: {line!r}"))
            else:
                issues.append(LintIssue(path, line_no, f"unexpected objects content {line!r}"))
            continue

        if state == "object":
            assert current_object is not None
            valid_keys = OBJECT_KEYS.get(current_object, {})
            if line == "#end_object":
                missing = REQUIRED_KEYS.get(current_object, set()) - object_seen_keys
                for key in sorted(missing):
                    issues.append(LintIssue(path, line_no, f"{current_object} missing required {key}"))
                current_object = None
                object_seen_keys = set()
                state = "objects"
            elif line in valid_keys:
                object_seen_keys.add(line)
                idx, value_issues = _consume_values(path, lines, idx, line, valid_keys[line], current_object)
                issues.extend(value_issues)
            elif line.startswith("##") and f"#{line[2:]}" in valid_keys:
                fixed_key = f"#{line[2:]}"
                issues.append(
                    LintIssue(path, line_no, f"unknown {current_object} directive {line!r}; did you mean {fixed_key!r}?")
                )
                idx, value_issues = _consume_values(path, lines, idx, fixed_key, valid_keys[fixed_key], current_object)
                issues.extend(value_issues)
            elif line.startswith("#"):
                issues.append(LintIssue(path, line_no, f"unknown {current_object} directive {line!r}"))
            else:
                issues.append(LintIssue(path, line_no, f"unexpected {current_object} value {line!r}"))
            continue

        if state == "done" and not _is_comment_or_blank(line):
            issues.append(LintIssue(path, line_no, f"content after ##end: {line!r}"))

    if not seen_scene:
        issues.append(LintIssue(path, 1, "missing ##scene section"))
    if state == "scene":
        issues.append(LintIssue(path, lines[-1][0] if lines else 1, "scene section missing #end_env"))
    if not seen_objects:
        issues.append(LintIssue(path, 1, "missing ##objects section"))
    if state == "object" and current_object is not None:
        issues.append(LintIssue(path, lines[-1][0] if lines else 1, f"{current_object} object missing #end_object"))
    if state == "objects":
        issues.append(LintIssue(path, lines[-1][0] if lines else 1, "objects section missing ##end"))

    return issues


def lint_file(path: Path) -> list[LintIssue]:
    try:
        text = path.read_text(encoding="utf-8")
    except OSError as exc:
        return [LintIssue(path, 0, str(exc))]

    issues = _lint_text(path, text)
    try:
        parse_scene_file(path)
    except SceneParseError as exc:
        issues.append(LintIssue(path, 0, f"parser error: {exc}"))
    except OSError as exc:
        issues.append(LintIssue(path, 0, str(exc)))
    return issues


def _expand_paths(paths: list[str]) -> list[Path]:
    if paths:
        return [Path(path) for path in paths]
    return sorted(Path("map").glob("*.scene")) + sorted(Path("map").glob("*.map"))


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Lint RTv1 scene/map files.")
    parser.add_argument("paths", nargs="*", help="files to lint; defaults to map/*.scene and map/*.map")
    parser.add_argument("--quiet", action="store_true", help="only print errors")
    args = parser.parse_args(argv)

    paths = _expand_paths(args.paths)
    if not paths:
        print("scene_lint: no files to lint", file=sys.stderr)
        return 1

    total_issues = 0
    for path in paths:
        issues = lint_file(path)
        if issues:
            total_issues += len(issues)
            for issue in issues:
                print(issue.format())
        elif not args.quiet:
            print(f"{path}: OK")

    return 1 if total_issues else 0


if __name__ == "__main__":
    raise SystemExit(main())
