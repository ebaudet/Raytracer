#!/usr/bin/env python3
"""Parser and validator for RTv1 scene/map files.

The C raytracer reads scene descriptions from stdin. This module parses the
same line-oriented format into Python dataclasses and can also be used as a
small CLI to inspect maps as JSON.
"""

from __future__ import annotations

import argparse
import json
import sys
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Iterable, Iterator


class SceneParseError(ValueError):
    """Raised when a scene file is structurally invalid."""


@dataclass(frozen=True)
class Vector:
    x: float
    y: float
    z: float


@dataclass(frozen=True)
class Color:
    value: int
    red: int
    green: int
    blue: int


@dataclass(frozen=True)
class SceneHeader:
    name: str | None
    window: tuple[int, int]
    cam: Vector
    c_runtime_cam: Vector


@dataclass(frozen=True)
class SceneObject:
    type: str
    origin: Vector | None = None
    direction: Vector | None = None
    color: Color | None = None
    radius: float | None = None
    const: float | None = None
    ref: int = 0


@dataclass(frozen=True)
class Scene:
    header: SceneHeader
    objects: list[SceneObject]


class _LineStream:
    def __init__(self, lines: Iterable[str]) -> None:
        self._lines: Iterator[tuple[int, str]] = (
            (idx, line.rstrip("\n\r")) for idx, line in enumerate(lines, 1)
        )
        self.current_no = 0

    def next(self, context: str = "unexpected end of file") -> str:
        try:
            return self._next_line()
        except StopIteration as exc:
            raise SceneParseError(context) from exc

    def __iter__(self) -> "_LineStream":
        return self

    def __next__(self) -> str:
        return self._next_line()

    def _next_line(self) -> str:
        self.current_no, line = next(self._lines)
        return line.strip()


def _number(raw: str, what: str, line_no: int) -> float:
    try:
        return float(raw)
    except ValueError as exc:
        raise SceneParseError(f"line {line_no}: {what} is not a number: {raw!r}") from exc


def _integer(raw: str, what: str, line_no: int) -> int:
    value = _number(raw, what, line_no)
    if not value.is_integer():
        raise SceneParseError(f"line {line_no}: {what} must be an integer: {raw!r}")
    return int(value)


def _vector(lines: _LineStream, what: str) -> Vector:
    x = _number(lines.next(f"missing {what} x"), f"{what} x", lines.current_no)
    y = _number(lines.next(f"missing {what} y"), f"{what} y", lines.current_no)
    z = _number(lines.next(f"missing {what} z"), f"{what} z", lines.current_no)
    return Vector(x, y, z)


def _color(raw: str, line_no: int) -> Color:
    if not raw.startswith("0x") or len(raw) < 3:
        raise SceneParseError(f"line {line_no}: color must be hexadecimal like 0xFF7260")
    try:
        value = int(raw[2:], 16)
    except ValueError as exc:
        raise SceneParseError(f"line {line_no}: invalid hexadecimal color: {raw!r}") from exc
    return Color(value=value, red=(value >> 16) & 0xFF, green=(value >> 8) & 0xFF, blue=value & 0xFF)


def _required(fields: dict[str, object], names: Iterable[str], object_type: str, line_no: int) -> None:
    missing = [name for name in names if fields.get(name) is None]
    if missing:
        raise SceneParseError(
            f"line {line_no}: {object_type} missing required field(s): {', '.join(missing)}"
        )


def _parse_header(lines: _LineStream) -> SceneHeader:
    name: str | None = None
    window: tuple[int, int] | None = None
    cam: Vector | None = None

    for line in lines:
        if line == "#end_env":
            break
        if line == "#name":
            name = lines.next("missing scene name")
        elif line == "#window":
            width = _integer(lines.next("missing window width"), "window width", lines.current_no)
            height = _integer(lines.next("missing window height"), "window height", lines.current_no)
            window = (width, height)
        elif line == "#cam":
            cam = _vector(lines, "camera")
    else:
        raise SceneParseError("scene header has no #end_env")

    if window is None or cam is None:
        raise SceneParseError("scene header requires #window and #cam")
    return SceneHeader(name=name, window=window, cam=cam, c_runtime_cam=Vector(cam.x, cam.y, cam.z - 1800))


def _parse_object(lines: _LineStream, object_type: str) -> SceneObject:
    fields: dict[str, object] = {
        "type": object_type,
        "origin": None,
        "direction": None,
        "color": None,
        "radius": None,
        "const": None,
        "ref": 0,
    }

    for line in lines:
        if line == "#end_object":
            break
        if line == "#origin":
            fields["origin"] = _vector(lines, f"{object_type} origin")
        elif line == "#dir":
            fields["direction"] = _vector(lines, f"{object_type} direction")
        elif line == "#color":
            fields["color"] = _color(lines.next(f"missing {object_type} color"), lines.current_no)
        elif line == "#radius":
            fields["radius"] = _number(lines.next(f"missing {object_type} radius"), f"{object_type} radius", lines.current_no)
        elif line == "#const":
            fields["const"] = _number(lines.next(f"missing {object_type} const"), f"{object_type} const", lines.current_no)
        elif line == "#ref":
            fields["ref"] = _integer(lines.next(f"missing {object_type} ref"), f"{object_type} ref", lines.current_no)
    else:
        raise SceneParseError(f"{object_type} object has no #end_object")

    if object_type == "sphere":
        _required(fields, ("origin", "color", "radius"), object_type, lines.current_no)
    elif object_type == "plan":
        _required(fields, ("origin", "color", "const"), object_type, lines.current_no)
    elif object_type in {"cylinder", "cone"}:
        _required(fields, ("origin", "direction", "color", "const"), object_type, lines.current_no)
        fields["radius"] = fields["const"]
    elif object_type == "light":
        _required(fields, ("origin", "color"), object_type, lines.current_no)
    else:
        raise SceneParseError(f"unsupported object type: {object_type!r}")

    return SceneObject(**fields)  # type: ignore[arg-type]


def _parse_objects(lines: _LineStream) -> list[SceneObject]:
    objects: list[SceneObject] = []
    supported = {"sphere", "plan", "cylinder", "cone", "light"}

    for line in lines:
        if line == "##end":
            break
        if line != "#type":
            continue
        object_type = lines.next("missing object type after #type")
        if object_type not in supported:
            raise SceneParseError(f"line {lines.current_no}: unsupported object type: {object_type!r}")
        objects.append(_parse_object(lines, object_type))
    else:
        raise SceneParseError("objects section has no ##end")

    if not objects:
        raise SceneParseError("objects section is empty")
    return objects


def parse_scene_text(text: str) -> Scene:
    """Parse a scene/map file from a string."""

    lines = _LineStream(text.splitlines())
    header: SceneHeader | None = None
    objects: list[SceneObject] | None = None

    for line in lines:
        if line == "##scene":
            header = _parse_header(lines)
        elif line == "##objects":
            objects = _parse_objects(lines)

    if header is None:
        raise SceneParseError("missing ##scene section")
    if objects is None:
        raise SceneParseError("missing ##objects section")
    return Scene(header=header, objects=objects)


def parse_scene_file(path: str | Path) -> Scene:
    """Parse a scene/map file from disk."""

    return parse_scene_text(Path(path).read_text(encoding="utf-8"))


def scene_to_dict(scene: Scene) -> dict[str, object]:
    return asdict(scene)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Parse an RTv1 scene/map file and print JSON.")
    parser.add_argument("path", nargs="?", help="scene/map path; reads stdin when omitted")
    parser.add_argument("--compact", action="store_true", help="print compact JSON")
    args = parser.parse_args(argv)

    try:
        if args.path:
            scene = parse_scene_file(args.path)
        else:
            scene = parse_scene_text(sys.stdin.read())
    except OSError as exc:
        print(f"scene_parser: {exc}", file=sys.stderr)
        return 1
    except SceneParseError as exc:
        print(f"scene_parser: {exc}", file=sys.stderr)
        return 2

    indent = None if args.compact else 2
    print(json.dumps(scene_to_dict(scene), indent=indent))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
