/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 18:52:59 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/14 18:52:59 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"

# define WIDTH		1000
# define HEIGHT		1000
# define KEY_ESC	65307

typedef struct		s_struct
{
	char			type;
	int				color;
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

typedef struct		s_sphere
{
	char			type;
	int				color;
	t_vector		*position;
	double			radius;
	struct s_sphere	*next;
}					t_sphere;

typedef struct		s_light
{
	char			type;
	int				color;
	t_vector		*position;
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
	t_vector		*cam;
	t_light			*light;
}					t_data;

/*
** error.c
*/
void		ft_error(char *str);

/*
** rtv1.c
*/
void		rtv1(void);
void		init_scene(void);
void		display_screen(t_img *img);
void		color_pixel(t_img *img, int x, int y, t_ray *rayon);
void		display_scene(t_img *img);

/*
** vector.c
*/
t_vector	*vector_new(double x, double y, double z);
void		vector_del(t_vector *vector);
void		vector_set(t_vector *vector, double x, double y, double z);
t_vector	*vector_copy(t_vector *a);

/*
** vector_calculation.c
*/
void		vector_normalize(t_vector *v);
double		vector_dot(t_vector *a, t_vector *b);
t_vector	*vector_sub(t_vector *a, t_vector *b);

/*
** sphere.c
*/
int			sphere_new(t_vector *position, double radius, int color);
void		sphere_del(t_sphere *sphere);
int			intersection_sphere(t_sphere *sphere, t_ray *ray, double *t);

/*
** light.c
*/
t_light		*light_new(t_vector *position, int color);
void		light_del(t_light *light);

/*
** env.c
*/
t_win		*env_init(void);
void		env_del(void);

/*
** image.c
*/
t_img		*img_init(void);
void		img_del(t_img *img);
void		eb_put_pixel_to_img(t_img *img, int x, int y, int color);

/*
** ray.c
*/
t_ray		*ray_new(void);
void		ray_del(t_ray *rayon);

/*
** hook.c
*/
void		eb_mlx(void);
int			eb_mlx_key_hook(int keycode);
int			eb_expose_hook(t_img *img);

/*
** data.c
*/
t_data		*data_init(void);

/*
** color.c
*/
int			color_find(void *object, t_data *d, t_vector *ray_di
	, double coef);
int			color_lambert(int color, double lambert);
int			color_norm(int red, int green, int blue);

/*
** intersection.c
*/
void		*intersection(t_data *data, t_ray *ray, double *dist);
char		type_object(void *ptr);

#endif /* !RTV1_H */