/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 22:36:16 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/25 20:56:14 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

void		light_new(t_vector *position, int color)
{
	t_data		*data;
	t_light		*light;
	t_light		*tmp;

	data = data_init();
	light = (t_light *)malloc(sizeof(t_light));
	light->pos = position;
	light->color = color;
	light->next = NULL;
	if (data->light)
	{
		tmp = data->light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = light;
	}
	else
		data->light = light;
}

void		light_del(t_light *light)
{
	if (light)
	{
		vector_del(light->pos);
		free(light);
		light = NULL;
	}
}
