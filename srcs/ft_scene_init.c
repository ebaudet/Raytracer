/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:36:50 by gpetrov           #+#    #+#             */
/*   Updated: 2020/08/03 05:31:36 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"
#include "libft.h"

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
	data->cam = vector_new(data->x, data->y, data->z - 1800);
}

void			ft_scene_init(t_data *data, char **line, int fd)
{
	char		win;
	char		cam;

	win = '0';
	cam = '0';
	while (ft_strcmp(*line, "#end_env") != 0) {
		if (ft_strcmp(*line, "#name") == 0) {
			get_next_line(fd, line);
			data->scene_name = ft_strdup(*line);
		}
		else if (ft_strcmp("#window", *line) == 0 && (win = '1'))
			ft_scene_init_window(data, line, fd);
		else if (ft_strcmp(*line, "#cam") == 0 && (cam = '1'))
			ft_scene_init_cam(data, line, fd);
		if (get_next_line(fd, line) <= 0)
			ft_error("[ERROR SCENE] - No end for scene init");
	}
	if (cam == '0' || win == '0')
		ft_error("[ERROR SCENE] - No camera or window specifications");
}
