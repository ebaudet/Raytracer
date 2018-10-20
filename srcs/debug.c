/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 18:27:01 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 21:04:51 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"
#include "libft.h"

int eb_debug(char *str, int free_str)
{
	t_data	*data;

	data = data_init();
	if (!DEBUG || !data->debug)
		return 0;

	ft_putstr("[DEBUG] ");

	ft_putendl(str);
	if (free_str)
		eb_help_atextf(str);
	else
		eb_help_atext(str);
	return 1;
}
