/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 21:35:11 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/16 21:35:11 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

t_data	*data_init(void)
{
	static t_data	*data = NULL;

	if (data == NULL)
	{
		if (!(data = (t_data *)malloc(sizeof(t_data))))
			ft_error("erreur malloc");
	}
	return (data);
}
