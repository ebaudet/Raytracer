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

static t_sphere		*sphere_intersection(t_data *data, t_ray *ray, double *dist)
{
	t_sphere	*tmp;
	t_sphere	*current;

	current = NULL;
	tmp = data->sphere;
	while (tmp)
	{
		if (!intersection_sphere(tmp, ray, dist))
			current = tmp;
		tmp = tmp->next;
	}
	return (current);
}

void				*intersection(t_data *data, t_ray *ray, double *dist)
{
	void	*object;

	object = sphere_intersection(data, ray, dist);
	return (object);
}

char				type_object(void *ptr)
{
	if (ptr)
	{
		if ((((t_struct *)ptr))->type)
			return (((t_struct *)ptr)->type);
	}
	return (0);
}
