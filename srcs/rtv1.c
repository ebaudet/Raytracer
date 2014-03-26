/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 18:53:48 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/26 18:01:50 by gpetrov          ###   ########.fr       */
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
	ft_parse_scene(data);
	/* cone_new(vector_new(-100, 0, -500), 0.100 */
/* 	, color_norm(200, 200, 200) */
/* 	, vector_new(0, 0, 1)); */
}

void	display_screen(t_img *img)
{
	int			x;
	int			y;
	t_ray		*rayon;
	t_data		*d;

	d = data_init();
	rayon = ray_new();
	y = 0;
	while (y < d->win_size_y)
	{
		x = 0;
		while (x < d->win_size_x)
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
	vector_set(&b, x - (d->win_size_x / 2), y - (d->win_size_y / 2), 0);
	vector_set(&ray_dir, b.x - d->cam->x, b.y - d->cam->y, b.z - d->cam->z);
	vector_normalize(&ray_dir);
	vector_set(rayon->o, d->cam->x, d->cam->y, d->cam->z);
	vector_set(rayon->d, ray_dir.x, ray_dir.y, ray_dir.z);
	vector_normalize(rayon->d);
	coef = 200000;
	inter = intersection(d, rayon, &coef);
	if (inter != NULL && coef < 200000)
	{
		color = color_find(inter, &ray_dir, coef);
		eb_put_pixel_to_img(img, x, y, color);
	}
}

void	display_scene(t_img *img)
{
	display_screen(img);
}
