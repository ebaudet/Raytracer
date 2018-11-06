/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 00:56:14 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 16:57:08 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "rtv1.h"
#include "libft.h"

void			eb_help_atext(char *str)
{
	t_data	*data;
	char	*tmp;

	data = data_init();
	tmp = ft_concat2endl(data->help_text, str);
	if (data->help_text != NULL) {
		free(data->help_text);
	}
	data->help_text = tmp;
}

void			eb_help_atextf(char *str)
{
	eb_help_atext(str);
	free(str);
}

void			eb_help_text(char *str)
{
	t_data	*data;

	data = data_init();
	if (data->help_text != NULL) {
		free(data->help_text);
	}
	data->help_text = str;
}

static int		eb_help_content(t_win *env, t_data *data)
{
	int		i;
	char	**str;


	str = ft_strsplit(data->help_text, '\n');
	if (str)
	{
		i = -1;
		while (*(str + ++i)) {
			mlx_string_put(env->mlx, env->win, 20, 53 + i * 11, 0xFF99FF,
			"|                                          |");
			mlx_string_put(env->mlx, env->win, 31, 53 + i * 11, 0x66D6ED,
		 		*(str+i));
			free(*(str+i));
		}
		free(str);
		return i;
	}
	return 0;
}

void			eb_help()
{
	t_win		*env;
	int			nb_lines;
	t_data		*data;

	data = data_init();
	if (data->help == 0)
		return ;
	eb_expose_hook(data->img);
	env = env_init();
	mlx_string_put(env->mlx, env->win, 20, 20, 0xFF99FF,
		"+------------------------------------------+");
	mlx_string_put(env->mlx, env->win, 20, 31, 0xFF99FF,
		"|                === HELP ===              |");
	mlx_string_put(env->mlx, env->win, 20, 42, 0xFF99FF,
		"|                                          |");
	nb_lines = eb_help_content(env, data);
	mlx_string_put(env->mlx, env->win, 20, 53 + nb_lines * 11, 0xFF99FF,
		"|                                          |");
	mlx_string_put(env->mlx, env->win, 20, 53 + (nb_lines+1) * 11, 0xFF99FF,
		"+------------------------------------------+");
}
