/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:55:41 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 21:10:04 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

int		color_find(void *object, t_vector *ray_dir, double coef)
{
	t_light		*light;
	int			color;
	t_vector	impact;
	double		dist;
	t_ray		*ray_light;

	color = get_color(object);
	light = data_init()->light;
	ray_light = ray_new();
	calcul_impact(&impact, ray_dir, coef);
	vector_set_copy(ray_light->o, &impact);
	while (light)
	{
		dist = dist_ab(light->pos, &impact);
		vector_sub_assoc(ray_light->d, light->pos, &impact);
		vector_normalize(ray_light->d);
		if (!intersection(data_init(), ray_light, &dist))
		{
			color = color_lambert(object, light, &impact, color);
			color = color_speculaire(object, light, &impact, color);
		}
		light = light->next;
	}
	color = color_reflexion(object, ray_dir, &impact, color);
	return (color);
}

int		color_speculaire(void *object, t_light *light, t_vector *impact
	, int color)
{
	double		spec;
	t_vector	shine;
	t_vector	normal;

	vect_normal(&normal, impact, object);
	vector_sub_assoc(&shine, impact, light->pos);
	vector_normalize(&shine);
	vector_mult(&shine, &shine, -1);
	spec = vector_dot(&shine, &normal);
	if (spec > 0)
		color = color_mult(color, pow(spec, 50));
	return (color);
}

int		color_reflexion(void *object, t_vector *ray_dir, t_vector *impact
	, int color)
{
	t_ray		reflexion;
	t_vector	pouet;
	t_vector	normal;
	int			new_color;
	static int	how_many = 1;

	if (type_object(object) != 's')
		return (color);
	if (how_many == 0)
	{
		how_many = 1;
		return (color);
	}
	how_many--;
	vect_normal(&normal, impact, object);
	vector_mult(&pouet, &normal, 2 * vector_dot(ray_dir, &normal));
	reflexion.d = vector_sub(ray_dir, &pouet);
	reflexion.o = vector_copy(impact);
	if ((new_color = color_pixel(&reflexion, 200000)) == 0)
		return (color);
	color = color_add(color, new_color, 100);
	return (color);
}

int		color_lambert(void *object, t_light *light, t_vector *impact, int color)
{
	double		lambert;
	t_vector	normal;
	t_vector	diffusion;

	vect_normal(&normal, impact, object);
	vector_sub_assoc(&diffusion, light->pos, impact);
	vector_normalize(&diffusion);
	lambert = vector_dot(&diffusion, &normal);
	color = color_mult(color, lambert);
	return (color);
}
