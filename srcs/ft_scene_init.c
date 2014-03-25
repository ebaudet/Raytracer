/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:36:50 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/25 20:49:52 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

static void		ft_scene_init_window(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - window's width is not a digit");
	data->win_size_x = ft_atoi(*line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - window's height is not a digit");
	data->win_size_y = ft_atoi(*line);
}

static void		ft_scene_init_cam(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - cam_x is not a digit");
	data->x = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - cam_y is not a digit");
	data->y = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - cam_z is not a digit");
	data->z = ft_atod(line);
	data->cam = vector_new(data->x, data->y, -(1000 / (2 * tan(M_PI / 12))));
}

void			ft_scene_init(t_data *data, char **line, int fd)
{
	while (ft_strcmp(*line, "#end_env") != 0)
	{
		if (ft_strcmp(*line, "#name") == 0)
		{
			get_next_line(fd, line);
			data->scene_name = ft_strdup(*line);
		}
		else if (ft_strcmp("#window", *line) == 0)
			ft_scene_init_window(data, line, fd);
		else if (ft_strcmp(*line, "#cam") == 0)
			ft_scene_init_cam(data, line, fd);
		get_next_line(fd, line);
	}
}
