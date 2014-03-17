/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 22:14:22 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/14 22:14:22 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "rtv1.h"

t_win	*env_init(void)
{
	static t_win	*win = NULL;

	if (win == NULL)
	{
		if (!(win = (t_win *)malloc(sizeof(t_win))))
			ft_error("erreur malloc");
		win->mlx = mlx_init();
		win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "RTV1");
		win->img = img_init();
	}
	return (win);
}

void	env_del(void)
{
	t_win	*win;

	win = env_init();
	if (win)
	{
		free(win->mlx);
		free(win->win);
		img_del(win->img);
		free(win);
		win = NULL;
	}
}
