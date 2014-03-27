/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 21:13:21 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 21:13:49 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

void		vector_add(t_vector *vector, t_vector *a, t_vector *b)
{
	vector->x = a->x + b->x;
	vector->y = a->y + b->y;
	vector->z = a->z + b->z;
}

double		dist_ab(t_vector *a, t_vector *b)
{
	double		dist;

	dist = sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2)
		+ pow(a->z - b->z, 2));
	return (dist);
}
