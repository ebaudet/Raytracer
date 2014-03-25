/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 15:21:33 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/25 15:57:40 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

double		ft_atod(char **str)
{
	double	value;
	int		sign;
	int		i;

	value = 0;
	sign = (**str == '-') ? -1 : 1;
	if (**str == '-' || **str == '+')
		(*str)++;
	while (ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		i = 1;
		while (ft_isdigit(**str))
		{
			value += (double)(**str - '0') / pow(10, i++);
			(*str)++;
		}
	}
	*str += 2;
	return (value * sign);
}

int		ft_check_if_nbr(char *str)
{
	int		i;
	int		dot;

	i = 0;
	dot = 0;
	if (str[0] == '\0')
		return (-1);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i] != 0)
	{
		if ((str[i] >= '0' && str[i] <= '9'))
			i++;
		else if (str[i] == '.')
		{
			dot++;
			if (dot > 1)
				return (-1);
			i++;
		}
		else
			return (-1);
	}
	return (1);
}
