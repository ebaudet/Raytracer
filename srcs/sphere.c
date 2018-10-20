/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 21:19:42 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/24 18:14:36 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "rtv1.h"
#include "libft.h"

void		sphere_new(t_vector *position, double radius, int color)
{
	t_data		*data;
	t_sphere	*sphere;
	t_sphere	*tmp;

	data = data_init();
	if ((sphere = (t_sphere *)ft_memalloc(sizeof(t_sphere))) == NULL)
		ft_error("error malloc");
	sphere->type = 's';
	sphere->color = color;
	sphere->ref = (color >> 24) % 256;
	sphere->pos = position;
	sphere->radius = radius;
	sphere->next = NULL;
	if (data->sphere)
	{
		tmp = data->sphere;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = sphere;
	}
	else
		data->sphere = sphere;
}

void		sphere_del(t_sphere *sphere)
{
	if (sphere)
	{
		vector_del(sphere->pos);
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

	dist = vector_sub(sphere->pos, ray->o);
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
