/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 15:21:33 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/27 20:53:37 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"
#include "libft.h"

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

int			ft_check_if_nbr(char *str)
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

void		ft_error_init(char *origin, char *dir, char *color, char *co)
{
	*origin = '0';
	*dir = '0';
	*color = '0';
	*co = '0';
}

char		type_object(void *ptr)
{
	if (ptr)
	{
		if ((((t_struct *)ptr))->type)
			return (((t_struct *)ptr)->type);
	}
	return (0);
}

int			ft_hextod(char *hex)
{
	int		result;
	int		lenght;
	char	c;
	int 	i;

	lenght = ft_strlen(hex);
	if (lenght < 3 || hex[0] != '0' || hex[1] != 'x') {
		return -1;
	}
	result = 0;
	i = 0;
	while (lenght - ++i >= 2) {
		c = hex[lenght - i];
		if (c >= '0' && c <= '9')
			result += (c - '0') * pow(16, i - 1);
		else if (c >= 'a' && c <= 'f')
			result += (c - 'a' + 10) * pow(16, i - 1);
		else if (c >= 'A' && c <= 'F')
			result += (c - 'A' + 10) * pow(16, i - 1);
		else {
			return -1;
		}
	}
	return result;
}

