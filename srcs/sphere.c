/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 21:19:42 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/14 21:19:42 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "rtv1.h"

t_sphere	*sphere_new(t_vector *position, double radius, int color)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->position = position;
	sphere->radius = radius;
	sphere->color = color;
	return (sphere);
}

void		sphere_del(t_sphere *sphere)
{
	if (sphere)
	{
		vector_del(sphere->position);
		free(sphere);
		sphere = NULL;
	}
}

int			intersection_sphere(t_sphere *sphere, t_ray *ray, double *t)
{
	t_vector	*dist;
	double		b;
	double		delta;
	double		t0;
	double		t1;

	dist = vector_copy(sphere->position);
	dist = vector_sub(dist, ray->o);
	b = 2 * vector_dot(ray->d, dist);
	delta = vector_dot(dist, dist) - pow(sphere->radius, 2);
	delta = pow(b, 2) - 4 * delta;
	if (delta < 0)
		return (-1);
	t0 = (b - sqrt(delta)) / (2);
	t1 = (b + sqrt(delta)) / (2);
	if ((t0 > 0.1) && (t0 < *t))
		*t = t0;
	if ((t1 > 0.1) && (t1 < *t))
		*t = t1;
	if ((*t == t0) || (*t == t1))
		return (0);
	return (-1);
}
