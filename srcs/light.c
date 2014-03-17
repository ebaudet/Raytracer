/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 22:36:16 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/16 22:36:16 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

t_light		*light_new(t_vector *position, int color)
{
	t_light		*light;

	light = (t_light *)malloc(sizeof(t_light));
	light->position = position;
	light->color = color;
	return (light);
}

void		light_del(t_light *light)
{
	if (light)
	{
		vector_del(light->position);
		free(light);
		light = NULL;
	}
}
