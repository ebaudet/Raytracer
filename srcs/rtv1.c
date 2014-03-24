/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 18:53:48 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/25 00:18:41 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include "rtv1.h"

void	rtv1(void)
{
	/* t_data		*data; */

/* 	data = data_init(); */
	init_scene();
	eb_mlx();
}

void	init_scene(void)
{
	t_data		*data;

	data = data_init();

	/*sphere_new(vector_new(180, 0, -1000), 50, 0xAA0022);
	ft_parse_scene(data);
	 sphere_new(vector_new(180, 0, -1000), 50, 0xAA0022); */
	/* sphere_new(vector_new(0, 50, -1500), 30, 0xCC2EFA); */
	sphere_new(vector_new(0, -50, -700), 10, 0xFFBF00);
	/* sphere_new(vector_new(50, 0, -800), 20, 0xC8FE2E); */
	/* sphere_new(vector_new(-150, 0, -900), 80, 0x2E9AFE); */

	/* plan_new(vector_new(0, 1, 0), -100, 0xBDBDBD); */
/*
	sphere_new(vector_new(180, 0, -1000), 50, 0xAA0022);
	sphere_new(vector_new(0, 50, -1500), 30, 0xCC2EFA);
	sphere_new(vector_new(0, -50, -700), 10, 0xFFBF00);
	sphere_new(vector_new(50, 0, -800), 20, 0xC8FE2E);
	
	sphere_new(vector_new(-150, 0, -900), 80, 0x2E9AFE);
	
	plan_new(vector_new(0, 1, 0), -100, 0xBDBDBD);*/
	/*plan_new(vector_new(20, 0, 1), -400, 0x5882FA);
	plan_new(vector_new(-20, 0, 1), -400, 0xF4FA58);*/
	/*plan_new(vector_new(0, 0, 1), -100, 0xFFFFFF);*/

/*	cylinder_new(vector_new(-200, 500, -500), 50, 0xAA0022, vector_new(0, 0, 1));
*/	/*cylinder_new(vector_new(0, 500, 0), 50, 0xBDBDBD, vector_new(0, 0, 1));*/
	cylinder_new(vector_new(150, 20, -50), 50, 0x2E9AFE, vector_new(0, 0, 1));
	cylinder_new(vector_new(0, 20, 50), 50, 0x2E9AFE, vector_new(0, 0, 1));
	cylinder_new(vector_new(-500, 20, 2000), 50, 0xFFFFFF, vector_new(0, 0, 1));

	/*plan_new(vector_new(0, 0, 1), -5000, 0xF6E3CE);*/
	/*plan_new(vector_new(4000, -2000, -5000), 4000, 0xBCF5A9);*/
	/*plan_new(vector_new(0, 0, 10000), 0, 0xF6E3CE);*/
	/* data->cam = vector_new(0, 0, -(WIDTH / (2 * tan(M_PI / 12)))); */
	data->light	= light_new(vector_new(500, -1000, -4000), 0xFAFAFA);
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
