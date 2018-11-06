/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:09 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/25 21:43:17 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_nbchar(double d, unsigned int precision)
{
	int		i;

	i = 0;
	if (precision > 0)
		i = precision + 1;
	if (d < 0) {
		i++;
		d = ft_fabs(d);
	}
	i += ceil(log10(d));
	return d;
}

static void put_decimals(double d, unsigned int precision, char *str)
{
	char	*tmp;
	double	decimals;
	int		i;
	int		symbol;

	if (precision == 0)
		return;
	symbol = 1;
	if (d < 0)
		symbol = -1;
	decimals = d - (int)d;
	decimals = ft_fabs(decimals);
	ft_strcat(str, ".");
	i = 0;
	while (++i <= (int)precision)
		decimals *= 10;
	decimals += 0.5;
	tmp = ft_itoa((int)decimals);
	ft_strcat(str, tmp);
	free(tmp);
}

char	*ft_dtoa(double d, unsigned int precision)
{
	char	*str;
	char	*tmp;

	str = ft_memalloc(ft_nbchar(d, precision) + 1);
	tmp = ft_itoa((int)d);
	str = ft_strcat(str, tmp);
	free(tmp);
	put_decimals(d, precision, str);
	return str;
}
