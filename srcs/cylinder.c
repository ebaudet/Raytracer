/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 01:19:35 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/24 19:32:59 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "rtv1.h"

void		cylinder_new(t_vector *pos, double radius, int color, t_vector *dir)
{
	t_data		*data;
	t_cylind	*cylinder;
	t_cylind	*tmp;

	data = data_init();
	if ((cylinder = (t_cylind *)malloc(sizeof(t_cylind))) == NULL)
		ft_error("error malloc");
	cylinder->type = 'c';
	cylinder->color = color;
	cylinder->pos = pos;
	cylinder->radius = radius;
	cylinder->dir = dir;
	cylinder->next = NULL;
	if (data->cylinder)
	{
		tmp = data->cylinder;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = cylinder;
	}
	else
		data->cylinder = cylinder;
}

void		cylinder_del(t_cylind *cylinder)
{
	if (cylinder)
	{
		vector_del(cylinder->pos);
		free(cylinder);
		cylinder = NULL;
	}
}

int			intersection_cylinder(t_cylind *cylinder, t_ray *ray, double *t)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	rslt;

	a = pow(ray->d->x, 2) + pow(ray->d->z, 2);
	b = (2 * (ray->d->x * (ray->o->x - cylinder->pos->x)))
		+ (2 * (ray->d->z * (ray->o->z - cylinder->pos->z)));
	c = pow(ray->o->x - cylinder->pos->x, 2)
		+ pow(ray->o->z - cylinder->pos->z, 2) - pow(cylinder->radius, 2);
	d = b * b - 4 * a * c;
	if (d > 0)
	{
		if ((((-b - sqrt(d)) / (2 * a)) - 0.000001) > 0)
			rslt = (-b - sqrt(d)) / (2 * a) - 0.000001;
		else
			rslt = (-b + sqrt(d)) / (2 * a) - 0.000001;
		if (rslt < *t)
		{
			*t = rslt;
			return (0);
		}
	}
	return (-1);
}

/*
int			intersection_cylinder(t_cylind *cylinder, t_ray *ray, double *t)
{
	t_vector	*dist;
	t_vector	*a;
	double		w;

	dist = vector_sub(cylinder->position, ray->o);
	w = vector_dot(ray->d, cylinder->direction);
	if (pow(b, 2) == 0)
	{
		a = vector_mult()
	}
}
*/
