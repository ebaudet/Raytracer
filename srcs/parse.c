/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 19:12:04 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/27 20:50:17 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

void		ft_objects_init(t_data *data, char **line, int fd)
{
	char	error_object;
	int		ret;

	error_object = '0';
	while (ft_strcmp("##end", *line) != 0 && ret > 0)
	{
		if (ft_strcmp("#type", *line) == 0)
		{
			get_next_line(fd, line);
			if (ft_strcmp("sphere", *line) == 0 && (error_object = '1'))
				ft_set_sphere(data, line, fd);
			else if (ft_strcmp("plan", *line) == 0 && (error_object = '1'))
				ft_set_plan(data, line, fd);
			else if (ft_strcmp("light", *line) == 0 && (error_object = '1'))
				ft_set_light(data, line, fd);
			else if (ft_strcmp("cylinder", *line) == 0 && (error_object = '1'))
				ft_set_cylinder(data, line, fd);
			else if (ft_strcmp("cone", *line) == 0 && (error_object = '1'))
				ft_set_cone(data, line, fd);
		}
		if ((ret = get_next_line(fd, line)) <= 0 && error_object == '0')
			ft_error("[ERROR - SCENE] - OBJ init");
	}
	if (error_object == '0')
		ft_error("[ERROR - SCENE] - No Objects");
}

void		ft_parse_scene(t_data *data)
{
	char	*line;
	int		fd;
	char	error_scene;
	char	error_object;

	fd = 0;
	error_scene = '0';
	error_object = '0';
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp("##scene", line) == 0)
		{
			ft_scene_init(data, &line, fd);
			error_scene = '1';
		}
		else if (ft_strcmp("##objects", line) == 0)
		{
			ft_objects_init(data, &line, fd);
			error_object = '1';
		}
	}
	if (error_scene == '0')
		ft_error("[ERROR - SCENE] - No scene");
	if (error_object == '0')
		ft_error("[ERROR - SCENE] - No objects");
}
