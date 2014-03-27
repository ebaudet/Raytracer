/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 18:27:01 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 21:04:51 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

int		get_color(void *object)
{
	int		color;

	color = ((t_struct *)object)->color;
	color = color_shadow(color, 0.2);
	return (color);
}

int		color_set(int red, int green, int blue, char reflect)
{
	int		color;

	reflect = (reflect > 100 ? 100 : reflect);
	red = (red > 0xFF ? 0xFF : red);
	green = (green > 0xFF ? 0xFF : green);
	blue = (blue > 0xFF ? 0xFF : blue);
	reflect = (reflect < 0x00 ? 0x00 : reflect);
	red = (red < 0x00 ? 0x00 : red);
	green = (green < 0x00 ? 0x00 : green);
	blue = (blue < 0x00 ? 0x00 : blue);
	color = (reflect << 24) + (red << 16) + (green << 8) + blue;
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
