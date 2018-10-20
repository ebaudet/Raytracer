/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/18 21:43:50 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/22 01:21:58 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"
#include "libft.h"

void		plan_new(t_vector *normal, int constante, int color)
{
	t_data		*data;
	t_plan		*plan;
	t_plan		*tmp;

	data = data_init();
	if ((plan = (t_plan *)ft_memalloc(sizeof(t_plan))) == NULL)
		ft_error("error malloc");
	plan->type = 'p';
	plan->color = color;
	plan->ref = (color >> 24) % 256;
	plan->normal = normal;
	vector_normalize(plan->normal);
	plan->constante = constante;
	plan->next = NULL;
	if (data->plan)
	{
		tmp = data->plan;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = plan;
	}
	else
		data->plan = plan;
}

void		plan_del(t_plan *plan)
{
	if (plan)
	{
		vector_del(plan->normal);
		free(plan);
		plan = NULL;
	}
}

int			intersection_plan(t_plan *plan, t_ray *ray, double *t)
{
	double		alpha;

	alpha = vector_dot(plan->normal, ray->o) + plan->constante;
	alpha = -alpha;
	alpha = alpha / vector_dot(plan->normal, ray->d);
	if ((alpha > 0.1) && (alpha < *t))
	{
		*t = alpha;
		return (0);
	}
	return (-1);
}
