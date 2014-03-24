/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 19:14:17 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/24 19:31:48 by ebaudet          ###   ########.fr       */
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

static t_plan		*plan_intersection(t_data *data, t_ray *ray, double *dist)
{
	t_plan		*tmp;
	t_plan		*current;

	current = NULL;
	tmp = data->plan;
	while (tmp)
	{
		if (!intersection_plan(tmp, ray, dist))
			current = tmp;
		tmp = tmp->next;
	}
	return (current);
}

static t_cylind		*cylind_intersection(t_data *data, t_ray *ray, double *dist)
{
	t_cylind	*tmp;
	t_cylind	*current;

	current = NULL;
	tmp = data->cylinder;
	while (tmp)
	{
		if (!intersection_cylinder(tmp, ray, dist))
			current = tmp;
		tmp = tmp->next;
	}
	return (current);
}

void				*intersection(t_data *data, t_ray *ray, double *dist)
{
	void	*object;
	void	*tmp;

	object = sphere_intersection(data, ray, dist);
	if ((tmp = plan_intersection(data, ray, dist)) != NULL)
		object = tmp;
	if ((tmp = cylind_intersection(data, ray, dist)) != NULL)
		object = tmp;
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
