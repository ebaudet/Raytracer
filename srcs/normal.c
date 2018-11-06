/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 20:07:22 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 22:07:31 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	vect_normal(t_vector *normal, t_vector *impact, void *object)
{
	if (type_object(object) == 's')
	{
		vector_sub_assoc(normal, impact, ((t_sphere *)object)->pos);
	}
	if (type_object(object) == 'p')
	{
		vector_set_copy(normal, ((t_plan *)object)->normal);
		if (vector_dot(normal, impact) >= 0)
			vector_mult(normal, normal, -1);
	}
	if (type_object(object) == 'c')
	{
		vector_set(normal, impact->x - ((t_cylind *)object)->pos->x, 0
			, impact->z - ((t_cylind *)object)->pos->z);
	}
	if (type_object(object) == 'o')
	{
		vector_set(normal, impact->x - ((t_cone *)object)->pos->x
			, 0, impact->z - ((t_cone *)object)->pos->z);
	}
	vector_normalize(normal);
}
