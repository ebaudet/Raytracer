/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:49:18 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/27 19:38:43 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

static void		ft_set_cylinder_origin(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's origin x is not a digit");
	data->x = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's origin y is not a digit");
	data->y = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's origin z is not a digit");
	data->z = ft_atod(line);
}

static void		ft_set_cylinder_dir(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's dir x is not a digit");
	data->x2 = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's dir y is not a digit");
	data->y2 = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's dir z is not a digit");
	data->z2 = ft_atod(line);
}

static void		ft_set_cylinder_const(int *cons, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's const is not a digit");
	*cons = ft_atoi(*line);
}

static void		ft_set_cylinder_color(t_data *data, char **line, int fd)
{
	int		color;

	get_next_line(fd, line);
	color = ft_hextod(*line);
	if (color == -1)
		ft_error("[ERROR SCENE] - Cylinder's color is not hexadecimal");
	data->r = (double)((color >> 16) % 256);
	data->g = (double)((color >> 8) % 256);
	data->b = (double)(color % 256);
}

void			ft_set_cylinder(t_data *data, char **line, int fd)
{
	int			cons;

	data->ref = 0;
	ft_error_init(&data->origin, &data->dir, &data->color, &data->co);
	while (ft_strcmp("#end_object", *line) != 0)
	{
		if (ft_strcmp("#origin", *line) == 0 && (data->origin = '1'))
			ft_set_cylinder_origin(data, line, fd);
		else if (ft_strcmp("#dir", *line) == 0 && (data->dir = '1'))
			ft_set_cylinder_dir(data, line, fd);
		else if (ft_strcmp("#const", *line) == 0 && (data->co = '1'))
			ft_set_cylinder_const(&cons, line, fd);
		else if (ft_strcmp("#color", *line) == 0 && (data->color = '1'))
			ft_set_cylinder_color(data, line, fd);
		else if (ft_strcmp("#ref", *line) == 0)
			ft_set_cylinder_ref(&data->ref, line, fd);
		if (get_next_line(fd, line) <= 0)
			ft_error("[ERROR OBJECT] - Object cylinder has no end");
	}
	if (data->origin == '0' || data->dir == '0' ||
		data->co == '0' || data->color == '0')
		ft_error("[ERROR OBJECT] - Cylinder's spec missing");
	cylinder_new(vector_new(data->x, data->y, data->z), cons
	, color_set(data->r, data->g, data->b, data->ref)
	, vector_new(data->x2, data->y2, data->z2));
}
