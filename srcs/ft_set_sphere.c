/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:39:23 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/27 19:51:50 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

static void		ft_set_sphere_rad(char **line, int fd, double *radius)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Sphere's radius is not a digit");
	*radius = ft_atod(line);
}

static void		ft_set_sphere_origin(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Sphere's origin x is not a digit");
	data->x = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Sphere's origin y is not a digit");
	data->y = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Sphere's origin z is not a digit");
	data->z = ft_atod(line);
}

static void		ft_set_sphere_color(t_data *data, char **line, int fd)
{
	int color;

	get_next_line(fd, line);
	color = ft_hextod(*line);
	if (color == -1)
		ft_error("[ERROR SCENE] - Sphere's color is not hexadecimal");
	data->x2 = (double)((color >> 16) % 256);
	data->y2 = (double)((color >> 8) % 256);
	data->z2 = (double)(color % 256);
}

static void		ft_set_sphere_norm_fuck(char *rad, char *origin, char *color)
{
	*rad = '0';
	*origin = '0';
	*color = '0';
}

void			ft_set_sphere(t_data *data, char **line, int fd)
{
	double		radius;
	char		rad;

	data->ref = 0;
	ft_set_sphere_norm_fuck(&rad, &data->origin, &data->color);
	while (ft_strcmp("#end_object", *line) != 0)
	{
		if (ft_strcmp("#radius", *line) == 0 && (rad = '1'))
			ft_set_sphere_rad(line, fd, &radius);
		else if (ft_strcmp("#origin", *line) == 0 && (data->origin = '1'))
			ft_set_sphere_origin(data, line, fd);
		else if (ft_strcmp("#color", *line) == 0 && (data->color = '1'))
			ft_set_sphere_color(data, line, fd);
		else if (ft_strcmp("#ref", *line) == 0)
			ft_set_sphere_ref(line, fd, &data->ref);
		if (get_next_line(fd, line) <= 0)
			ft_error("[ERROR OBJECT] - Object sphere has no end");
	}
	if (rad == '0' || data->origin == '0' || data->color == '0')
		ft_error("[OBJECT ERROR] - Sphere's spec missing");
	sphere_new(vector_new(data->x, data->y, data->z), radius \
	, color_set((int)data->x2, (int)data->y2, (int)data->z2, data->ref));
}
