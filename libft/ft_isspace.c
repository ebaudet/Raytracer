/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:09 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/25 21:43:17 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

int		ft_isspace(int c)
{
	char	search[7] = " \t\n\v\f\r\0";

	if (ft_strchr(search, c) == NULL)
		return 0;
	return 1;
}
