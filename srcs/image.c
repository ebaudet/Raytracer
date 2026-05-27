/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 22:07:33 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/24 21:24:26 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include "rtv1.h"
#include "libft.h"

t_img		*img_init(void)
{
	t_win	*win;
	t_img	*img;
	t_data	*data;

	data = data_init();
	win = env_init();
	img = (t_img *)ft_memalloc(sizeof(t_img));
	img->img = mlx_new_image(win->mlx, data->win_size_x, data->win_size_y);
	img->data = mlx_get_data_addr(img->img, &img->bpp, &img->size_line
		, &img->endian);
	return (img);
}

void		img_del(t_img *img)
{
	if (img)
	{
		if (img->img != NULL)
			free(img->img);
		free(img);
		img = NULL;
	}
}

void		eb_put_pixel_to_img(t_img *img, int x, int y, int color)
{
	t_win			*env;
	unsigned int	mgcv;
	int				i;
	int			bytes_per_pixel;

	env = env_init();
	mgcv = mlx_get_color_value(env->mlx, color);
	bytes_per_pixel = img->bpp / 8;
	i = x * bytes_per_pixel + y * img->size_line;
	if (img->endian == 0)
	{
		img->data[i] = (mgcv & 0xFF);
		if (bytes_per_pixel > 1)
			img->data[i + 1] = (mgcv & 0xFF00) >> 8;
		if (bytes_per_pixel > 2)
			img->data[i + 2] = (mgcv & 0xFF0000) >> 16;
		if (bytes_per_pixel > 3)
			img->data[i + 3] = 0xFF;
	}
	else
	{
		if (bytes_per_pixel == 4)
		{
			img->data[i] = 0xFF;
			img->data[i + 1] = (mgcv & 0xFF0000) >> 16;
			img->data[i + 2] = (mgcv & 0xFF00) >> 8;
			img->data[i + 3] = (mgcv & 0xFF);
		}
		else
		{
			img->data[i] = (mgcv & 0xFF);
			if (bytes_per_pixel > 1)
				img->data[i + 1] = (mgcv & 0xFF00) >> 8;
			if (bytes_per_pixel > 2)
				img->data[i + 2] = (mgcv & 0xFF0000) >> 16;
		}
	}
}
