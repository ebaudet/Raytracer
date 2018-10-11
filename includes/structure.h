/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 21:21:07 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 21:22:19 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct		s_struct
{
	char			type;
	int				color;
	char			ref;
}					t_struct;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_ray
{
	char			type;
	t_vector		*o;
	t_vector		*d;
}					t_ray;

typedef struct		s_cone
{
	char			type;
	int				color;
	char			ref;
	t_vector		*pos;
	double			radius;
	t_vector		*dir;
	struct s_cone	*next;
}					t_cone;

typedef struct		s_plan
{
	char			type;
	int				color;
	char			ref;
	t_vector		*normal;
	int				constante;
	struct s_plan	*next;
}					t_plan;

typedef struct		s_sphere
{
	char			type;
	int				color;
	char			ref;
	t_vector		*pos;
	double			radius;
	struct s_sphere	*next;
}					t_sphere;

typedef struct		s_cylind
{
	char			type;
	int				color;
	char			ref;
	t_vector		*pos;
	double			radius;
	t_vector		*dir;
	struct s_cylind	*next;
}					t_cylind;

typedef struct		s_light
{
	char			type;
	int				color;
	char			ref;
	t_vector		*pos;
	struct s_light	*next;
}					t_light;

typedef struct		s_img
{
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_win
{
	void			*mlx;
	void			*win;
	t_img			*img;
}					t_win;

typedef struct		s_data
{
	t_sphere		*sphere;
	t_plan			*plan;
	t_cylind		*cylinder;
	t_cone			*cone;
	t_vector		*cam;
	t_light			*light;
	char			*scene_name;
	char			origin;
	char			dir;
	char			color;
	char			co;
	char			ref;
	double			x;
	double			y;
	double			z;
	double			x2;
	double			y2;
	double			z2;
	double			r;
	double			g;
	double			b;
	int				win_size_x;
	int				win_size_y;
	void			*current;
	int				debug;
}					t_data;

#endif
