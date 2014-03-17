/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 21:17:22 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/14 21:17:22 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

t_vector	*vector_new(double x, double y, double z)
{
	t_vector	*v;

	v = (t_vector *)malloc(sizeof(t_vector));
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}

void		vector_del(t_vector *vector)
{
	if (vector)
	{
		free(vector);
		vector = NULL;
	}
}

void		vector_set(t_vector *vector, double x, double y, double z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

t_vector	*vector_copy(t_vector *a)
{
	t_vector	*v;

	v = (t_vector *)malloc(sizeof(t_vector));
	v->x = a->x;
	v->y = a->y;
	v->z = a->z;
	return (v);
}
