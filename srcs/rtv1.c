/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 18:53:48 by ebaudet           #+#    #+#             */
/*   Updated: 2020/08/03 04:44:58 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include "rtv1.h"
#include "libft.h"

void	rtv1(void)
{
	rand_init();
	init_scene();
	eb_mlx();
}

void	init_scene(void)
{
	t_data		*data;

	data = data_init();
	ft_parse_scene(data);
}

void	display_pixel(t_img *img, int x, int y, t_ray *rayon)
{
	t_data		*d;
	t_vector	b;
	t_vector	ray_dir;
	int			color;

	d = data_init();
	vector_set(&b, x - (d->win_size_x / 2), y - (d->win_size_y / 2), 0);
	vector_set(&ray_dir, b.x - d->cam->x, b.y - d->cam->y, b.z - d->cam->z);
	vector_normalize(&ray_dir);
	vector_set(rayon->o, d->cam->x, d->cam->y, d->cam->z);
	vector_set(rayon->d, ray_dir.x, ray_dir.y, ray_dir.z);
	vector_normalize(rayon->d);
	color = color_pixel(rayon, 200000, DEPTH);
	eb_debug(ft_concat2("couleur du pixel : ", ft_lutohex(color)), 1);
	eb_put_pixel_to_img(img, x, y, color);
}

int		color_pixel(t_ray *rayon, double coef, int depth)
{
	t_data		*d;
	void		*inter;
	int			color;

	d = data_init();
	d->current = NULL;
	inter = intersection(d, rayon, &coef);
	if (inter != NULL && coef < 200000)
	{
		eb_debug_object(inter);
		d->current = inter;
		color = color_find(inter, rayon->d, coef, depth);
		return (color);
	}
	if (depth < DEPTH)
		return 0; // no stars for reflect part.
	return (rand_color(1, 1000, color_norm(0,0,0)));
}

void	display_scene(t_img *img)
{
	int			x;
	int			y;
	t_ray		*rayon;
	t_data		*d;
	int			time;

	d = data_init();
	rayon = ray_new();
	time = 0;
	y = 0;
	while (y < d->win_size_y)
	{
		x = 0;
		while (x < d->win_size_x)
		{
			display_pixel(img, x, y, rayon);
			x++;
			time++;
			if (time % 100000 == 0)
				eb_waiting(time/100000);
		}
		y++;
	}
}
