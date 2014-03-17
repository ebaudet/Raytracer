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
	data->sphere = sphere_new(vector_new(0, 0, 0), 300, 0xAA0022);
	data->cam = vector_new(0, 0, -(WIDTH / (2 * tan(M_PI / 12))));
	data->light	= light_new(vector_new(0, 0, 500), 0xFAFAFA);
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
	int			intersection;

	d = data_init();
	b.x = x - (WIDTH / 2);
	b.y = y - (HEIGHT / 2);
	b.z = 0;
	ray_dir.x = b.x - d->cam->x;
	ray_dir.y = b.y - d->cam->y;
	ray_dir.z = b.z - d->cam->z;
	vector_normalize(&ray_dir);
	vector_set(rayon->o, d->cam->x, d->cam->y, d->cam->z);
	vector_set(rayon->d, ray_dir.x, ray_dir.y, ray_dir.z);
	coef = 200000;
	intersection = intersection_sphere(d->sphere, rayon, &coef);
	if (intersection != -1 && coef < 200000)
	{
		intersection = color_find(d->sphere->color, d, &ray_dir, coef);
		eb_put_pixel_to_img(img, x, y, intersection);
	}
}

void	display_scene(t_img *img)
{
	display_screen(img);
}
