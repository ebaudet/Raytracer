/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_ref.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 21:49:26 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/27 22:03:28 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

void		ft_set_cone_ref(char *ref, char **line, int fd)
{
	if (get_next_line(fd, line) <= 0)
		ft_error("[ERROR] - End of File");
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's reflexion is not a digit");
	*ref = ft_atoi(*line);
}

void		ft_set_cylinder_ref(char *ref, char **line, int fd)
{
	if (get_next_line(fd, line) <= 0)
		ft_error("[ERROR] - End of File");
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cylinder's reflexion is not a digit");
	*ref = ft_atoi(*line);
}

void		ft_set_sphere_ref(char **line, int fd, char *ref)
{
	if (get_next_line(fd, line) <= 0)
		ft_error("[ERROR] - End of File");
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Sphere's reflexion is not a digit");
	*ref = ft_atoi(*line);
}
