/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 22:19:34 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/16 22:19:34 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "rtv1.h"

void		vector_normalize(t_vector *v)
{
	double		id;

	id = 1 / sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	v->x = v->x * id;
	v->y = v->y * id;
	v->z = v->z * id;
}

double		vector_dot(t_vector *a, t_vector *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

t_vector	*vector_sub(t_vector *a, t_vector *b)
{
	t_vector	*v;

	v = (t_vector *)malloc(sizeof(t_vector));
	v->x = a->x - b->x;
	v->y = a->y - b->y;
	v->z = a->z - b->z;
	return (v);
}
