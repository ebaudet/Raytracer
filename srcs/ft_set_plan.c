/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:41:07 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/25 20:57:19 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_set_plan_const(int *cons, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Plan's const is not a digit");
	*cons = ft_atoi(*line);
}

static void		ft_set_plan_origin(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Plan's origin x is not a digit");
	data->x = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Plan's origin y is not a digit");
	data->y = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Plan's origin z is not a digit");
	data->z = ft_atod(line);
}

static void		ft_set_plan_color(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Plan's color RED is not a digit");
	data->x2 = (double)ft_atoi(*line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Plan's color GREEN is not a digit");
	data->y2 = (double)ft_atoi(*line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Plan's color BLUE is not a digit");
	data->z2 = (double)ft_atoi(*line);
}

static void		ft_set_plan_ref(t_data *data, char **line, int fd)
{
	
	if (get_next_line(fd, line) <= 0)
		ft_error("[ERROR] - End of File");
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Plan's reflexion is not a digit");
	*ref = ft_atoi(line);
}

void			ft_set_plan(t_data *data, char **line, int fd)
{
	int			cons;
	char		origin;
	char		color;
	char		co;
	char		ref;

	origin = '0';
	color = '0';
	co = '0';
	while (ft_strcmp("#end_object", *line) != 0)
	{
		if (ft_strcmp("#const", *line) == 0 && (co = '1'))
			ft_set_plan_const(&cons, line, fd);
		else if (ft_strcmp("#origin", *line) == 0 && (origin = '1'))
			ft_set_plan_origin(data, line, fd);
		else if (ft_strcmp("#color", *line) == 0 && (color = '1'))
			ft_set_plan_color(data, line, fd);
		else if (ft_strcmp("#ref", *line) == 0 && (ref = '1'))
			ft_set_plan_ref(&ref, line, fd);
		if (get_next_line(fd, line) <= 0)
			ft_error("[ERROR OBJECT] - Object plan has no end");
	}
	if (origin == '0' || co == '0' || color == '0')
		ft_error("[ERROR OBJECT] - Plan's spec missing");
	plan_new(vector_new(data->x, data->y, data->z), cons
	, color_set((int)data->x2, (int)data->y2, (int)data->z2), ref);
}
