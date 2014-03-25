/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:49:18 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/25 20:51:10 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's color RED is not a digit");
	data->r = (double)ft_atoi(*line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's color GREEN is not a digit");
	data->g = (double)ft_atoi(*line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's color BLUE is not a digit");
	data->b = (double)ft_atoi(*line);
}

void			ft_set_cylinder(t_data *data, char **line, int fd)
{
	int			cons;

	while (ft_strcmp("#end_object", *line) != 0)
	{
		if (ft_strcmp("#origin", *line) == 0)
			ft_set_cylinder_origin(data, line, fd);
		else if (ft_strcmp("#dir", *line) == 0)
			ft_set_cylinder_dir(data, line, fd);
		else if (ft_strcmp("#const", *line) == 0)
			ft_set_cylinder_const(&cons, line, fd);
		else if (ft_strcmp("#color", *line) == 0)
			ft_set_cylinder_color(data, line, fd);
		get_next_line(fd, line);
	}
	cylinder_new(vector_new(data->x, data->y, data->z), cons
	, color_norm(data->r, data->g, data->b)
	, vector_new(data->x2, data->y2, data->z2));
}
