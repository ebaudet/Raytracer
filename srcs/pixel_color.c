/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:55:41 by ebaudet           #+#    #+#             */
/*   Updated: 2018/12/22 19:01:59 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

int		color_find(void *object, t_vector *ray_dir, double coef, int depth)
{
	t_light		*light;
	int			color;
	t_vector	impact;
	double		dist;
	t_ray		*ray_light;
	int 		color_calc;

	// color = get_color(object);
	color = 0x010101;
	// color = 0xffffff;
	light = data_init()->light;
	ray_light = ray_new();
	calcul_impact(&impact, ray_dir, coef);
	vector_set_copy(ray_light->o, &impact);
	while (light)
	{
		dist = dist_ab(light->pos, &impact);
		vector_sub_assoc(ray_light->d, light->pos, &impact);
		vector_normalize(ray_light->d);
		color_calc = 0x000000;
		if (!intersection(data_init(), ray_light, &dist))
		{
			color_calc = color_lambert(object, light, &impact, color_calc);
			color_calc = color_add(color_calc, color_speculaire(object, light, &impact, color_calc), 100);
			color_calc = color_filter(color_calc, light->color);

			// color = color_add(color, color_light(color, light->color), 30);
			// eb_debug(ft_sprintf("couleur add : %p\ncouleur light : %p\n", color,
			                    // light->color), 1);
			// color_calc = color_add(color_calc, light->color, 50);
			// color = color_middle(color, light->color);
		}
		color = color_add(color, color_calc, 100);
		light = light->next;
	}
	color = color_filter(get_color(object), color);
	if (((t_struct*)object)->ref > 0)
		color = color_reflexion(object, ray_dir, &impact, color, depth);
	// eb_debug(ft_sprintf("couleur object : %p\ncouleur light : %p\n",get_color(object), color), 1);
	// eb_debug_object(object);
	// eb_debug(ft_sprintf("couleur final : %p\n", color), 1);

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
	, int color, int depth)
{
	t_ray		reflexion;
	t_vector	tmp;
	t_vector	normal;
	int			new_color;

	if (((t_struct *)object)->ref == 0)
		return (color);
	if (depth <= 0)
		return color;
	vect_normal(&normal, impact, object);
	eb_debug("inside color_reflexion\n", 0);
	// eb_debug(ft_sprintf("ray_dir(%f,%f,%f).normal(%f,%f,%f)=%f\n", ray_dir->x, ray_dir->y, ray_dir->z, normal.x, normal.y, normal.z, vector_dot(ray_dir, &normal)), 0);

	// if ((double)vector_dot(ray_dir, &normal) < (double)0.00) {
		// eb_debug("vector_dot < 0\n", 0);
		// return (color);
	// }
	vector_mult(&tmp, &normal, 2 * vector_dot(ray_dir, &normal));
	reflexion.d = vector_sub(ray_dir, &tmp);
	vector_normalize(reflexion.d);
	reflexion.o = vector_copy(impact);
	new_color = color_pixel(&reflexion, 200000, --depth);
	color = color_middle(color, new_color, ((t_struct *)object)->ref);
	return (color);
}

int		color_lambert(void *object, t_light *light, t_vector *impact, int color)
{
	double		lambert;
	t_vector	normal;
	t_vector	diffusion;
	int			color_lambert;
	// double		dist;

	// dist = dist_ab(light->pos, impact);
	color_lambert = 0xFFFFFF;
	// color_lambert = color_shadow(color_lambert, 10 / pow(dist / 100, 2));
	vect_normal(&normal, impact, object);
	vector_sub_assoc(&diffusion, light->pos, impact);
	vector_normalize(&diffusion);
	lambert = vector_dot(&diffusion, &normal);
	color_lambert = color_mult(color_lambert, lambert);
	color = color_add(color, color_lambert, 100);
	return (color);
}
