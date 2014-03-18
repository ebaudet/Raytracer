/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 22:37:09 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/16 22:37:09 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		color_find(void *object, t_data *d, t_vector *ray_dir, double coef)
{
	double		lambert;
	t_vector	impact;
	t_vector	normal;
	t_vector	light;
	int			color;

	impact.x = d->cam->x + coef * ray_dir->x;
	impact.y = d->cam->y + coef * ray_dir->y;
	impact.z = d->cam->z + coef * ray_dir->z;
	if (type_object(object) == 's')
	{
		normal.x = impact.x - ((t_sphere *)object)->position->x;
		normal.y = impact.y - ((t_sphere *)object)->position->y;
		normal.z = impact.z - ((t_sphere *)object)->position->z;
	}
	light.x = d->light->position->x - impact.x;
	light.y = d->light->position->y - impact.y;
	light.z = d->light->position->z - impact.z;
	vector_normalize(&light);
	vector_normalize(&normal);
	lambert = vector_dot(&light, &normal);
	color = color_lambert(((t_struct *)object)->color, lambert);
	return (color);
}

int		color_lambert(int color, double lambert)
{
	int		red;
	int		green;
	int		blue;

	red = (color >> 16) % 256;
	green = (color >> 8) % 256;
	blue = color % 256;
	red += red * lambert;
	green += green * lambert;
	blue += blue * lambert;
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
