/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:56:46 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 21:01:00 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		color_mult(int color, double mult)
{
	double		red;
	double		green;
	double		blue;

	mult = (mult < 0.0 ? 0 : mult);
	red = (color >> 16) % 256;
	green = (color >> 8) % 256;
	blue = color % 256;
	red = red * mult;
	green = green * mult;
	blue = blue * mult;
	color = color_norm((int)red, (int)green, (int)blue);
	return (color);
}

int		color_add(int color1, int color2, int rate)
{
	double		red;
	double		green;
	double		blue;

	rate = (rate > 100 ? 100 : rate);
	rate = (rate < 0 ? 0 : rate);
	red = (((int)color1 >> 16) % 256)
		+ (((int)color2 >> 16) % 256) * ((double)rate / 100);
	green = (((int)color1 >> 8) % 256)
		+ (((int)color2 >> 8) % 256) * ((double)rate / 100);
	blue = ((int)color1 % 256) + ((int)color2 % 256) * ((double)rate / 100);
	color1 = color_norm((int)red, (int)green, (int)blue);
	return (color1);
}

/*
 * color_midle :
 * rate should be between 0 and 100.
 * Define how muche color1 and color2 we put.
 * return color1 (100 - rate)%  and color2 rate%
 */
int		color_middle(int color1, int color2, int rate)
{
	double		red;
	double		green;
	double		blue;

	rate = (rate > 100 ? 100 : rate);
	rate = (rate < 0 ? 0 : rate);
	red = ((color1 >> 16) % 256) * ((100 - (double)rate) / 100)
		+ ((color2 >> 16) % 256) * ((double)rate / 100);
	green = ((color1 >> 8) % 256) * ((100 - (double)rate) / 100)
		+ ((color2 >> 8) % 256) * ((double)rate / 100);
	blue = (color1 % 256) * ((100 - (double)rate) / 100)
		+ (color2 % 256) * ((double)rate / 100);
	color1 = color_norm((int)red, (int)green, (int)blue);
	return (color1);
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
