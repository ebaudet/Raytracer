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

int		eb_mlx_mouse(int button,int x,int y, void *p)
{
	t_win		*env;
	t_data		*data;
	t_ray		*rayon;
	t_img		*img;

	env = env_init();
	data = data_init();
	data->debug = 1;
	// ft_printf("Mouse in Win[%p], button %d at %dx%d.\n",env->win, button, x, y);
	if (button == 1)
	{
		rayon = ray_new();
		img = img_init();
		eb_help_text(ft_sprintf("Mouse in Win[%p]\nbutton %d at %dx%d.\n",
			env->win, button, x, y));
		display_pixel(img, x, y, rayon);
		eb_help();
		img_del(img);
		ray_del(rayon);
	}
	data->debug = 0;
	return 0;
}

void	eb_mlx(void)
{
	t_win		*env;
	t_img		*img;
	t_data		*data;

	env = env_init();
	img = img_init();
	data = data_init();
	eb_waiting(0);
	display_scene(img);
	data->img = img;
	mlx_expose_hook(env->win, eb_expose_hook, img);
	mlx_key_hook(env->win, eb_mlx_key_hook, NULL);
	mlx_mouse_hook(env->win, eb_mlx_mouse, NULL);
	mlx_loop(env->mlx);
}

int		eb_mlx_key_hook(int keycode)
{
	t_data		*data;

	data = data_init();
	if (keycode == KEY_ESC || keycode == KEY_Q)
		ft_error("Merci pour le poisson.");
	if (keycode == 104) {
		if (data->help == 0) {
			data->help = 1;
			eb_help();
		} else {
			eb_expose_hook(data->img);
			data->help = 0;
		}
	}
	return (0);
}

int		eb_expose_hook(t_img *img)
{
	t_win		*env;

	env = env_init();
	mlx_put_image_to_window(env->mlx, env->win, img->img, 0, 0);
	return (0);
}

void	eb_waiting(unsigned int time)
{
	t_win		*env;
	t_data		*data;
	char		*str;
	char		*waiting_time;

	env = env_init();
	data = data_init();
	waiting_time = ft_strnew(time);
	waiting_time = ft_memset(waiting_time, '.', time);
	str = ft_concat2("Scene chargement", waiting_time);
	mlx_string_put(env->mlx, env->win, data->win_size_x/2, data->win_size_y/2,
		0xFF99FF,str);
	free(str);
	free(waiting_time);
}
