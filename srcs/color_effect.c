/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:58:45 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 21:05:56 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

int		color_filter(int color, int light)
{
	int		red;
	int		green;
	int		blue;

	red = ((color >> 16) % 256) * ((light >> 16) % 256) / 256;
	green = ((color >> 8) % 256) * ((light >> 8) % 256) / 256;
	blue = (color % 256) * (light % 256) / 256;
	return (color_norm(red, green, blue));
}
