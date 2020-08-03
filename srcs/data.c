/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 21:35:11 by ebaudet           #+#    #+#             */
/*   Updated: 2020/08/03 05:12:35 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"
#include "libft.h"

t_data	*data_init(void)
{
	static t_data	*data = NULL;

	if (data == NULL) {
		if (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
			ft_error("erreur malloc");
		data->help_text = ft_sprintf("    Click on the window to have the    \n"
									 "           associated info.          \n")
									 ->str;
	}
	return (data);
}
