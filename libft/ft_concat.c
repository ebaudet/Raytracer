/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:49 by ebaudet           #+#    #+#             */
/*   Updated: 2014/01/04 18:35:41 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_concat(const char *s1, const char *s2)
{
	char *res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res) {
		ft_strcpy(res, s1);
		ft_strcat(res, s2);
	}
	return res;
}
