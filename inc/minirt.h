/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:13:07 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/04 15:10:53 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <assert.h>

//System includes.
# include <math.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

//42 specific includes.
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"

//Prototypes to prevent breaking of dependencies
typedef struct s_parse		t_parse;
typedef struct s_minirt		t_minirt;
typedef struct s_color		t_color;
typedef struct s_tuple		t_tuple;
typedef struct s_light		t_light;
typedef struct s_material	t_material;
typedef struct s_scene_obj	t_scene_obj;
typedef struct s_camera		t_camera;
typedef struct s_comps		t_comps;
typedef struct s_light_vars	t_light_vars;

//Project includes.
# include "linear_algebra.h"
# include "raytracing.h"
# include "parsing.h"
# include "utils.h"
# include "dev.h" // remove before submitting

//Constant defines
/**
 * @todo  M_PI Only here to stop vscode annoyance. 
 */
# define M_PI			3.14159265358979323846
# define EPSILON		0.0001
# define EPS_ORIENT		0.1

typedef enum e_exit
{
	SUCCESS,
	FAIL,
}	t_exit;

//Attributes for viewport
typedef struct s_vp
{
	float	fov;
	float	aspect_ratio;
	float	vp_h;
	float	vp_w;
}	t_vp;

typedef struct s_minirt
{
	t_parse		*world;
	t_vp		*vp;
	mlx_image_t	*img;
	mlx_t		*mlx;
}		t_minirt;

//drawing
t_ray		ray_for_pixel(t_minirt *minirt, t_camera *c, int px, int py);
void		set_pixel_color(t_minirt *minirt);
void		render_world(t_minirt *minirt);
void		ft_keyhook(void *param);

//init.c
void		init_minirt(t_minirt *minirt);
t_material	init_material(float amb_col);
void		init_xs(t_xs *xs);
void		init_objects(t_minirt *minirt);

//error & cleanup
void		exit_error(t_minirt *minirt, const char *msg);
void		cleanup(t_minirt *minirt);

#endif
