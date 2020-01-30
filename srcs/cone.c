/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 14:45:26 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/27 21:54:32 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "rtv1.h"
#include "libft.h"

void		cone_new(t_vector *pos, double radius, int color, t_vector *dir)
{
	t_data	*data;
	t_cone	*cone;
	t_cone	*tmp;

	data = data_init();
	if ((cone = (t_cone *)ft_memalloc(sizeof(t_cone))) == NULL)
		ft_error("error malloc");
	cone->type = 'o';
	cone->color = color;
	cone->ref = (color >> 24) % 256;
	cone->pos = pos;
	cone->radius = radius;
	cone->dir = dir;
	cone->next = NULL;
	if (data->cone)
	{
		tmp = data->cone;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = cone;
	}
	else
		data->cone = cone;
}

void		cone_del(t_cone *cone)
{
	if (cone)
	{
		vector_del(cone->pos);
		free(cone);
		cone = NULL;
	}
}

int			intersection_cone(t_cone *cone, t_ray *ray, double *t)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	rslt;

	a = pow(ray->d->x, 2) + pow(ray->d->z, 2)
	- pow(ray->d->y * cone->radius, 2);
	b = (2 * (ray->d->x * (ray->o->x - cone->pos->x)))
		+ (2 * (ray->d->z * (ray->o->z - cone->pos->z)))
		- (2 * ray->d->y * (ray->o->y - cone->pos->y) * cone->radius);
	c = pow(ray->o->x - cone->pos->x, 2) + pow(ray->o->z - cone->pos->z, 2)
		- pow(ray->o->y - cone->pos->y, 2);
	d = b * b - 4 * a * c;
	if (d > 0)
	{
		if ((((-b - sqrt(d)) / (2 * a)) - 0.000001) > 0)
			rslt = (-b - sqrt(d)) / (2 * a) - 0.000001;
		else
			rslt = (-b + sqrt(d)) / (2 * a) - 0.000001;
		if (rslt < *t && (*t = rslt))
			return (0);
	}
	return (-1);
}

char		*print_cone(t_cone *o)
{
	char	*str;

	str = ft_sprintf("Type Objet : Cone\n"
	                 " - couleur :   %p\n"
	                 " - position :  (%f,%f,%f)\n"
	                 " - rayon :     %f\n"
	                 " - direction : (%f,%f,%f)\n"
	                 " - reflet :    %d",
	                 o->color, o->pos->x, o->pos->y,
	                 o->pos->z, o->radius, o->dir->x, o->dir->y,
	                 o->dir->z, (int)o->ref)->str;
	return str;
}

