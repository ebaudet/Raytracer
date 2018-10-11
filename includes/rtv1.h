/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 18:52:59 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/27 21:21:39 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WIDTH		1000			// largeur de la fenêtre
# define HEIGHT		500				// hauteur de la fenêtre
# define KEY_ESC	65307			// valeur numérique de la touche Escape
# define DEBUG      1				// option pour le debug

# include "structure.h"

/*
** error.c
*/
void		ft_error(char *str);

/*
** rtv1.c
*/
void		rtv1(void);
void		init_scene(void);
void		display_pixel(t_img *img, int x, int y, t_ray *rayon);
int			color_pixel(t_ray *rayon, double coef);
void		display_scene(t_img *img);

/*
** vector.c
*/
t_vector	*vector_new(double x, double y, double z);
void		vector_del(t_vector *vector);
void		vector_set(t_vector *vector, double x, double y, double z);
void		vector_set_copy(t_vector *vector, t_vector *copy);
t_vector	*vector_copy(t_vector *a);
t_vector	vector_return(double x, double y, double z);

/*
** normal.c
*/
void		vect_normal(t_vector *normal, t_vector *impact, void *object);

/*
** vector_calculation.c
*/
void		vector_normalize(t_vector *v);
double		vector_dot(t_vector *a, t_vector *b);
t_vector	*vector_sub(t_vector *a, t_vector *b);
void		vector_sub_assoc(t_vector *vector, t_vector *a, t_vector *b);
void		vector_mult(t_vector *vector, t_vector *a, double val);

/*
** vector_calculation2.c
*/
void		vector_add(t_vector *vector, t_vector *a, t_vector *b);
double		dist_ab(t_vector *a, t_vector *b);

/*
** sphere.c
*/
void		sphere_new(t_vector *position, double radius, int color);
void		sphere_del(t_sphere *sphere);
int			intersection_sphere(t_sphere *sphere, t_ray *ray, double *t);

/*
** plan.c
*/
void		plan_new(t_vector *normal, int constante, int color);
void		plan_del(t_plan *plan);
int			intersection_plan(t_plan *plan, t_ray *ray, double *t);

/*
** cylinder.c
*/
void		cylinder_new(t_vector *pos, double radius, int color
				, t_vector *dir);
void		cylinder_del(t_cylind *cylinder);
int			intersection_cylinder(t_cylind *cylinder, t_ray *ray, double *t);

/*
**	cone.c
*/
void		cone_new(t_vector *pos, double radius, int color, t_vector *dir);
void		cone_del(t_cone *cone);
int			intersection_cone(t_cone *cone, t_ray *ray, double *t);

/*
** light.c
*/
void		light_new(t_vector *position, int color);
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
** pixel_color.c
*/
int			color_find(void *object, t_vector *ray_dir, double coef);
int			color_speculaire(void *object, t_light *light, t_vector *impact
	, int color);
int			color_reflexion(void *object, t_vector *ray_dir, t_vector *impact
	, int color);
int			color_lambert(void *object, t_light *light, t_vector *impact
	, int color);

/*
** color_calculation.c
*/
int			color_mult(int color, double mult);
int			color_add(int color1, int color2, int rate);
int			color_middle(int color1, int color2);
int			color_norm(int red, int green, int blue);

/*
** color_effect.c
*/
int			color_shadow(int color, double shadow);
int			color_light(int color, int color2);

/*
** color.c
*/
int			get_color(void *object);
int			color_set(int red, int green, int blue, char reflect);
void		calcul_impact(t_vector *impact, t_vector *ray_dir, double coef);

/*
** intersection.c
*/
void		*intersection(t_data *data, t_ray *ray, double *dist);

/*
**	parse.c
*/
void		ft_parse_scene(t_data *data);
void		ft_objects_init(t_data *data, char **line, int fd);

/*
**	ft_scene_init.c
*/
void		ft_scene_init(t_data *data, char **line, int fd);

/*
**	ft_set_sphere.c
*/
void		ft_set_sphere(t_data *data, char **line, int fd);

/*
**	ft_set_plan.c
*/
void		ft_set_plan(t_data *data, char **line, int fd);

/*
**	ft_set_light.c
*/
void		ft_set_light(t_data *data, char **line, int fd);

/*
**	ft_set_cylinder.c
*/
void		ft_set_cylinder(t_data *data, char **line, int fd);

/*
**	ft_set_cone.c
*/
void		ft_set_cone(t_data *data, char **line, int fd);

/*
**	tools.c
*/
double		ft_atod(char **str);
int			ft_check_if_nbr(char *str);
void		ft_error_init(char *origin, char *dir, char *color, char *co);
char		type_object(void *ptr);

/*
**	ft_set_ref.c
*/
void		ft_set_cone_ref(char *ref, char **line, int fd);
void		ft_set_cylinder_ref(char *ref, char **line, int fd);
void		ft_set_sphere_ref(char **line, int fd, char *ref);

/*
**	random.c
*/
void		rand_init();
int			rand_limited(int min, int max);
int			rand_percent(int percent, int flow);
int			rand_color(int percent, int flow, int base_color);

/*
**	debug.c
*/
int			eb_debug(char *str);

#endif
