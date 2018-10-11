/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 00:56:14 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 16:57:08 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "rtv1.h"
#include "libft.h"
#include <stdio.h>

int		eb_mlx_mouse(int button,int x,int y, void *p)
{
	t_win		*env;
	t_data		*data;
	t_ray		*rayon;
	t_img		*img;

	env = env_init();
	data = data_init();
	img = img_init();
	data->debug = 1;
	rayon = ray_new();
	printf("Mouse in Win[%d], button %d at %dx%d.\n",env->win, button,x,y);
	display_pixel(img, x, y, rayon);
	img_del(img);
	ray_del(rayon);
	data->debug = 0;
	return 0;
}

void	eb_mlx(void)
{
	t_win		*env;
	t_img		*img;

	env = env_init();
	img = img_init();
	mlx_expose_hook(env->win, eb_expose_hook, img);
	mlx_key_hook(env->win, eb_mlx_key_hook, NULL);
	mlx_mouse_hook(env->win, eb_mlx_mouse, NULL);
	mlx_loop(env->mlx);
}

int		eb_mlx_key_hook(int keycode)
{
	if (keycode == KEY_ESC)
	{
		ft_error("Merci pour le poisson.");
	}
	return (0);
}

int		eb_expose_hook(t_img *img)
{
	t_win		*env;

	env = env_init();
	display_scene(img);
	mlx_put_image_to_window(env->mlx, env->win, img->img, 0, 0);
	return (0);
}
