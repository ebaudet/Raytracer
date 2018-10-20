/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutohex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 20:45:55 by ebaudet           #+#    #+#             */
/*   Updated: 2018/10/19 20:45:55 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_lutohex(long unsigned int lu)
{
	char				hexadecimalNumber[100];
	long unsigned int	temp;
	int					i;

	ft_memset(hexadecimalNumber, 0, 100);
	i = 0;
	while (lu != 0)
	{
		temp = lu % 16;
		if (temp < 10)
			temp = temp + '0';
		else
			temp = temp + 'a' - 10;
		hexadecimalNumber[i++] = temp;
		lu = lu / 16;
	}
	ft_strcat(hexadecimalNumber + i, "x0");
	ft_strreverse(hexadecimalNumber);
	return ft_strdup(hexadecimalNumber);
}
