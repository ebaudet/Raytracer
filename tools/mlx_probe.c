#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_probe
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	int		bpp;
	int		line;
	int		endian;
	int		phase;
	int		ticks;
	int		w;
	int		h;
}t_probe;

static void	put_px(t_probe *p, int x, int y, unsigned int rgb)
{
	int	i;

	if (x < 0 || y < 0 || x >= p->w || y >= p->h)
		return ;
	i = y * p->line + x * (p->bpp / 8);
	if (p->endian == 0)
	{
		p->buf[i + 0] = (char)(rgb & 0xFF);
		p->buf[i + 1] = (char)((rgb >> 8) & 0xFF);
		p->buf[i + 2] = (char)((rgb >> 16) & 0xFF);
		if ((p->bpp / 8) == 4)
			p->buf[i + 3] = 0x00;
	}
	else
	{
		if ((p->bpp / 8) == 4)
		{
			p->buf[i + 0] = 0x00;
			p->buf[i + 1] = (char)((rgb >> 16) & 0xFF);
			p->buf[i + 2] = (char)((rgb >> 8) & 0xFF);
			p->buf[i + 3] = (char)(rgb & 0xFF);
		}
	}
}

static void	draw_image_pattern(t_probe *p)
{
	int	x;
	int	y;
	unsigned int c;

	y = 0;
	while (y < p->h)
	{
		x = 0;
		while (x < p->w)
		{
			c = ((unsigned int)(x * 255 / (p->w - 1)) << 16)
				| ((unsigned int)(y * 255 / (p->h - 1)) << 8)
				| (unsigned int)(((x + y) / 2) % 256);
			if (((x / 24) + (y / 24)) % 2 == 0)
				c ^= 0x00202020;
			put_px(p, x, y, c);
			x++;
		}
		y++;
	}
}

#ifndef SKIP_PIXELPUT
static void	draw_pixel_put_pattern(t_probe *p)
{
	int i;
	int x;
	int y;

	mlx_clear_window(p->mlx, p->win);
	i = 0;
	while (i < p->w && i < p->h)
	{
		mlx_pixel_put(p->mlx, p->win, i, i, 0x00FF0000);
		mlx_pixel_put(p->mlx, p->win, p->w - 1 - i, i, 0x0000FF00);
		i += 2;
	}
	y = 40;
	while (y < p->h - 40)
	{
		x = 40;
		while (x < p->w - 40)
		{
			mlx_pixel_put(p->mlx, p->win, x, y, 0x000000FF);
			x += 18;
		}
		y += 18;
	}
}
#endif

static int	expose_cb(void *param)
{
	t_probe *p;

	p = (t_probe *)param;
	if (p->phase == 2)
		mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	return (0);
}

static int	key_cb(int keycode, void *param)
{
	(void)param;
	if (keycode == 53 || keycode == 65307 || keycode == 12 || keycode == 113)
		exit(0);
	return (0);
}

static int	loop_cb(void *param)
{
	t_probe *p;

	p = (t_probe *)param;
	p->ticks++;
#ifndef SKIP_PIXELPUT
	if (p->ticks == 1)
	{
		p->phase = 1;
		fprintf(stdout, "[mlx_probe] phase 1: mlx_pixel_put\n");
		draw_pixel_put_pattern(p);
		mlx_do_sync(p->mlx);
	}
	if (p->ticks == 120)
#else
	if (p->ticks == 1)
#endif
	{
		p->phase = 2;
		fprintf(stdout, "[mlx_probe] phase 2: image buffer + mlx_put_image_to_window\n");
		draw_image_pattern(p);
		mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
		mlx_do_sync(p->mlx);
	}
	return (0);
}

int	main(void)
{
	t_probe p;

	memset(&p, 0, sizeof(p));
	p.w = 900;
	p.h = 560;
	p.mlx = mlx_init();
	if (!p.mlx)
		return (fprintf(stderr, "mlx_init failed\n"), 1);
	p.win = mlx_new_window(p.mlx, p.w, p.h, "mlx_probe");
	if (!p.win)
		return (fprintf(stderr, "mlx_new_window failed\n"), 1);
	p.img = mlx_new_image(p.mlx, p.w, p.h);
	if (!p.img)
		return (fprintf(stderr, "mlx_new_image failed\n"), 1);
	p.buf = mlx_get_data_addr(p.img, &p.bpp, &p.line, &p.endian);
	fprintf(stdout, "[mlx_probe] bpp=%d line=%d endian=%d\n", p.bpp, p.line, p.endian);
	mlx_expose_hook(p.win, expose_cb, &p);
	mlx_key_hook(p.win, key_cb, &p);
	mlx_loop_hook(p.mlx, loop_cb, &p);
	mlx_loop(p.mlx);
	return (0);
}
