/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 19:14:17 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/17 19:47:07 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		intersection(t_data *data, t_ray *ray, double *dist)
{
	double	object_dist;

	object_dist = *dist;

}

char	type_object(void *ptr)
{
	if (ptr)
	{
		if (ptr->type)
			return (ptr->type);
	}
	return (0);
}
