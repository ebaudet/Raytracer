/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 18:53:48 by ebaudet           #+#    #+#             */
/*   Updated: 2020/08/03 02:14:07 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h> //Ne pas oublier d'inclure le fichier time.h
#include <stdbool.h>
#include "rtv1.h"


// initialisation de rand
void	rand_init()
{
	srand(time(NULL));
}

// On suppose min < max
//
int		rand_limited(int min, int max)
{
	if (min < max)
		return rand()%(max-min) + min;
	return rand()%(min-max) + max;
}

int		rand_percent(int percent, int flow)
{
	if (rand_limited(1, flow) <= percent)
		return 1;
	return 0;
}

int		rand_color(int percent, int flow, int base_color)
{
	if (rand_percent(percent,flow) == 1)
		return color_norm(rand_limited(0,255),rand_limited(0,255),rand_limited(0,255));
	return base_color;
}
