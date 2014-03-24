/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 19:12:04 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/24 23:57:15 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "rtv1.h"

double		ft_atod(char **str)
{
	double	value;
	int		sign;
	int		i;

	value = 0;
	sign = (**str == '-') ? -1 : 1;
	if (**str == '-' || **str == '+')
		(*str)++;
	while (ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		i = 1;
		while (ft_isdigit(**str))
		{
			value += (double)(**str - '0') / pow(10, i++);
			(*str)++;
		}
	}
	*str += 2;
	return (value * sign);
}

void		ft_scene_init(t_data *data, char **line, int fd)
{
	while (ft_strcmp(*line, "#end_env") != 0)
	{
		if (ft_strcmp(*line, "#name") == 0)
		{
			get_next_line(fd, line);
			data->scene_name = ft_strdup(*line);
		}
		else if (ft_strcmp("#window", *line) == 0)
		{
			get_next_line(fd, line);
			data->win_size_x = ft_atoi(*line);
			get_next_line(fd, line);
			data->win_size_y = ft_atoi(*line);
		}
		else if (ft_strcmp(*line, "#cam") == 0)
		{
			get_next_line(fd, line);
			data->x = ft_atod(line);
			get_next_line(fd, line);
			data->y = ft_atod(line);
			get_next_line(fd, line);
			data->z = ft_atod(line);
			data->cam = vector_new(data->x, data->y, -(1000 / (2 * tan(M_PI / 12))));
		}
		get_next_line(fd, line);
	}
}

void		ft_set_sphere(t_data *data, char **line, int fd)
{
	double	radius;
	int		r;
	int		g;
	int		b;

	while (ft_strcmp("#end_object", *line) != 0)
	{
		if (ft_strcmp("#radius", *line) == 0)
		{
			get_next_line(fd, line);
			radius = ft_atod(line);
		}
		else if (ft_strcmp("#origin", *line) == 0)
		{
			get_next_line(fd, line);
			data->x = ft_atod(line);
			get_next_line(fd, line);
			data->y = ft_atod(line);
			get_next_line(fd, line);
			data->z = ft_atod(line);
		}
		else if (ft_strcmp("#color", *line) == 0)
		{
			get_next_line(fd, line);
			r = ft_atoi(*line);
			get_next_line(fd, line);
			g = ft_atoi(*line);
			get_next_line(fd, line);
			b = ft_atoi(*line);
		}
		get_next_line(fd, line);
	}
	sphere_new(vector_new(data->x, data->y, data->z), radius, color_norm(r, g, b));
}

void		ft_set_plan(t_data *data, char **line, int fd)
{
	int		cons;
	int		r;
	int		g;
	int		b;

	while (ft_strcmp("#end_object", *line) != 0)
	{
		if (ft_strcmp("#const", *line) == 0)
		{
			get_next_line(fd, line);
			cons = ft_atoi(*line);
		}
		else if (ft_strcmp("#origin", *line) == 0)
		{
			get_next_line(fd, line);
			data->x = ft_atod(line);
			get_next_line(fd, line);
			data->y = ft_atod(line);
			get_next_line(fd, line);
			data->z = ft_atod(line);
		}
		else if (ft_strcmp("#color", *line) == 0)
		{
			get_next_line(fd, line);
			r = ft_atoi(*line);
			get_next_line(fd, line);
			g = ft_atoi(*line);
			get_next_line(fd, line);
			b = ft_atoi(*line);
		}
		get_next_line(fd, line);
	}
	plan_new(vector_new(data->x, data->y, data->z), cons, color_norm(r, g, b));
}

/* void		ft_set_light(t_data *data, char **line, int fd) */
/* { */
/* 	int		r; */
/* 	int		g; */
/* 	int		b; */

/* 	while (ft_strcmp("#end_object", *line) != 0) */
/* 	{ */
/* 		else if (ft_strcmp("#origin", *line) == 0) */
/* 		{ */
/* 			get_next_line(fd, line); */
/* 			data->x = ft_atod(line); */
/* 			get_next_line(fd, line); */
/* 			data->y = ft_atod(line); */
/* 			get_next_line(fd, line); */
/* 			data->z = ft_atod(line); */
/* 		} */
/* 		else if (ft_strcmp("#color", *line) == 0) */
/* 		{ */
/* 			get_next_line(fd, line); */
/* 			r = ft_atoi(*line); */
/* 			get_next_line(fd, line); */
/* 			g = ft_atoi(*line); */
/* 			get_next_line(fd, line); */
/* 			b = ft_atoi(*line); */
/* 		} */
/* 		get_next_line(fd, line); */
/* 	} */
/* 	data->light	= light_new(vector_new(data->x, data->y, data->z), color_norm(r, g, b)); */
/* } */

void		ft_objects_init(t_data *data, char **line, int fd)
{
	while (ft_strcmp("##end", *line) != 0)
	{
		if (ft_strcmp("#type", *line) == 0)
		{
			get_next_line(fd, line);
			if (ft_strcmp("sphere", *line) == 0)
				ft_set_sphere(data, line, fd);
			else if (ft_strcmp("plan", *line) == 0)
				ft_set_plan(data, line, fd);
			/* else if (ft_strcmp("light", *line) == 0) */
/* 				ft_set_light(data, line, fd); */
		}
		get_next_line(fd, line);
	}
}

void		ft_parse_scene(t_data *data)
{
	char	*line;
	int		fd;

	fd = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp("##scene", line) == 0)
			ft_scene_init(data, &line, fd);
		else if (ft_strcmp("##objects", line) == 0)
			ft_objects_init(data, &line, fd);
	}
}
