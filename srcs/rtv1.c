/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 18:53:48 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/14 18:53:48 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include "rtv1.h"

void	rtv1(void)
{
	init_scene();
	eb_mlx();
}

void	init_scene(void)
{
	t_data		*data;

	data = data_init();
	sphere_new(vector_new(0, 0, 3000), 50, 0xAA0022);
	sphere_new(vector_new(0, 500, 200), 300, 0xCC2EFA);
	sphere_new(vector_new(0, -500, 1000), 300, 0xFFBF00);
	sphere_new(vector_new(500, 0, 300), 300, 0xC8FE2E);
	sphere_new(vector_new(-500, 0, 2000), 300, 0x2E9AFE);
	plan_new(vector_new(5000, -3000, -5000), -1000, 0xBDBDBD);
	plan_new(vector_new(4000, -2000, -5000), 4000, 0xBCF5A9);
	/*plan_new(vector_new(0, 0, 10000), 0, 0xF6E3CE);*/
	data->cam = vector_new(0, 0, -(WIDTH / (2 * tan(M_PI / 12))));
	data->light	= light_new(vector_new(500, 0, 4000), 0xFAFAFA);
}

void	display_screen(t_img *img)
{
	int			x;
	int			y;
	t_ray		*rayon;

	rayon = ray_new();
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color_pixel(img, x, y, rayon);
			x++;
		}
		y++;
	}
}

void	color_pixel(t_img *img, int x, int y, t_ray *rayon)
{
	t_data		*d;
	t_vector	b;
	t_vector	ray_dir;
	double		coef;
	void		*inter;
	int			color;

	d = data_init();
	vector_set(&b, x - (WIDTH / 2), y - (HEIGHT / 2), 0);
	vector_set(&ray_dir, b.x - d->cam->x, b.y - d->cam->y, b.z - d->cam->z);
	vector_normalize(&ray_dir);
	vector_set(rayon->o, d->cam->x, d->cam->y, d->cam->z);
	vector_set(rayon->d, ray_dir.x, ray_dir.y, ray_dir.z);
	coef = 200000;

	/* calcul de l'intersection avec un objet */
	inter = intersection(d, rayon, &coef);
	if (inter != NULL && coef < 200000)
	{
		color = color_find(inter, d, &ray_dir, coef);
		eb_put_pixel_to_img(img, x, y, color);
	}
}

void	display_scene(t_img *img)
{
	display_screen(img);
}
