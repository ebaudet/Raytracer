/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 00:40:49 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/15 00:40:49 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

t_ray	*ray_new(void)
{
	t_ray	*rayon;

	rayon = (t_ray	*)malloc(sizeof(t_ray));
	rayon->o = vector_new(0, 0, 0);
	rayon->d = vector_new(0, 0, 0);
	return (rayon);
}

void	ray_del(t_ray *rayon)
{
	if (rayon)
	{
		vector_del(rayon->o);
		vector_del(rayon->d);
		free(rayon);
		rayon = NULL;
	}
}