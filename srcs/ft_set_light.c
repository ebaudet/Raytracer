/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:42:56 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/27 19:54:45 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

static void		ft_set_light_origin(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Light's origin x is not a digit");
	data->x = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Light's origin y is not a digit");
	data->y = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Light's origin z is not a digit");
	data->z = ft_atod(line);
}

static void		ft_set_light_color(t_data *data, char **line, int fd)
{
	int		color;

	get_next_line(fd, line);
	color = ft_hextod(*line);
	if (color == -1)
		ft_error("[ERROR SCENE] - Light's color is not hexadecimal");
	data->x2 = (double)((color >> 16) % 256);
	data->y2 = (double)((color >> 8) % 256);
	data->z2 = (double)(color % 256);
}

static void		ft_set_light_ref(char *ref, char **line, int fd)
{
	if (get_next_line(fd, line) <= 0)
		ft_error("[ERROR] - End of File");
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Light's reflexion is not a digit");
	*ref = ft_atoi(*line);
}

void			ft_set_light(t_data *data, char **line, int fd)
{
	char		origin;
	char		color;
	char		ref;

	origin = '0';
	color = '0';
	while (ft_strcmp("#end_object", *line) != 0)
	{
		if (ft_strcmp("#origin", *line) == 0 && (origin = '1'))
			ft_set_light_origin(data, line, fd);
		else if (ft_strcmp("#color", *line) == 0 && (color = '1'))
			ft_set_light_color(data, line, fd);
		else if (ft_strcmp("#ref", *line) == 0 && (ref = '1'))
			ft_set_light_ref(&ref, line, fd);
		if (get_next_line(fd, line) <= 0)
			ft_error("[ERROR OBJECT] - Object cone has no end");
	}
	if (origin == '0' || color == '0')
		ft_error("[ERROR OBJECT] - Cone's spec missing");
	light_new(vector_new(data->x, data->y, data->z)
	, color_set(data->x2, data->y2, data->z2, ref));
}
