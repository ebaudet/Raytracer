/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 18:27:01 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/26 01:21:54 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

int		get_color(void *object)
{
	int		color;

	color = ((t_struct *)object)->color;
	color = color_shadow(color, 0.5);
	return (color);
}

void	calcul_impact(t_vector *impact, t_vector *ray_dir, double coef)
{
	t_data		*d;

	d = data_init();
	impact->x = d->cam->x + coef * ray_dir->x;
	impact->y = d->cam->y + coef * ray_dir->y;
	impact->z = d->cam->z + coef * ray_dir->z;
}

int		color_speculaire(void *object, t_light *light, t_vector *impact, int color)
{
	double		spec;
	t_vector	shine;
	/*t_vector	reflect;*/
	t_vector	normal;

	vect_normal(&normal, impact, object);
	vector_sub_assoc(&shine, impact, light->pos);
	vector_normalize(&shine);
	/*vector_mult(&reflect, &normal, -2 * vector_dot(&shine, &normal));
	vector_sub_assoc(&reflect, &shine, &reflect);
	vector_normalize(&reflect);*/
	vector_mult(&shine, &shine, -1);
	/*spec = vector_dot(&shine, &reflect);*/
	spec = vector_dot(&shine, &normal);
	if (spec > 0)
		color = color_mult(color, pow(spec, 50));
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

int		color_find(void *object, t_vector *ray_dir, double coef)
{
	t_light		*light;
	int			color;
	t_vector	impact;
	/*int			deja_vu;*/

	color = get_color(object);
	light = data_init()->light;
	calcul_impact(&impact, ray_dir, coef);
	/*color = color_mult(color, pow((1 - (coef / 200000)), 150));*/
	while (light)
	{
		color = color_light(color_lambert(object, light, &impact, get_color(object)), color);
		color = color_speculaire(object, light, &impact, color);
		light = light->next;
	}
	return (color);
}

int		color_shadow(int color, double shadow)
{
	int		red;
	int		green;
	int		blue;

	red = (color >> 16) % 256;
	green = (color >> 8) % 256;
	blue = color % 256;
	red = red * shadow;
	green = green * shadow;
	blue = blue * shadow;
	color = color_norm(red, green, blue);
	return (color);
}

int		color_light(int color, int color2)
{
	int		red;
	int		green;
	int		blue;

	if (((color >> 16) % 256) > ((color2 >> 16) % 256))
		red = (color >> 16) % 256;
	else
		red = (color2 >> 16) % 256;

	if (((color >> 8) % 256) > ((color2 >> 8) % 256))
		green = (color >> 8) % 256;
	else
		green = (color2 >> 8) % 256;

	if (((color) % 256) > ((color2) % 256))
		blue = (color) % 256;
	else
		blue = (color2) % 256;
	color = color_norm(red, green, blue);
	return (color);
}

int		color_mult(int color, double mult)
{
	int		red;
	int		green;
	int		blue;

	/*mult = (mult < 0 ? 0 : mult);*/
	red = (color >> 16) % 256;
	green = (color >> 8) % 256;
	blue = color % 256;
	red += red * mult;
	green += green * mult;
	blue += blue * mult;
	color = color_norm(red, green, blue);
	return (color);
}

int		color_norm(int red, int green, int blue)
{
	int		color;

	red = (red > 0xFF ? 0xFF : red);
	green = (green > 0xFF ? 0xFF : green);
	blue = (blue > 0xFF ? 0xFF : blue);
	red = (red < 0x00 ? 0x00 : red);
	green = (green < 0x00 ? 0x00 : green);
	blue = (blue < 0x00 ? 0x00 : blue);
	color = (red << 16) + (green << 8) + blue;
	return (color);
}
