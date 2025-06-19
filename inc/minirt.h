#ifndef MINIRT_H
# define MINIRT_H

#include <assert.h>

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
typedef struct s_parse t_parse;
typedef struct s_minirt t_minirt;
typedef struct s_color t_color;
typedef struct s_tuple t_tuple;
typedef struct s_light t_light;
typedef struct	s_material t_material;
typedef struct	s_scene_obj t_scene_obj;
typedef struct	s_camera t_camera;
t_color	color(float r, float g, float b);
t_color	lighting(t_material m, t_light l, t_tuple p, t_tuple c_v, t_tuple n_v, bool in_shadow);

//Project includes.
# include "raytracing.h"
# include "parsing.h"
# include "utils.h"

//Constant defines
/**
 * @todo  M_PI Only here to stop vscode annoyance. Can be removed for evaluation.
 */
# define M_PI			3.14159265358979323846
# define EPSILON		0.0001

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

void	draw_current_thing(t_minirt *minirt, t_camera *c);
void	render_world(t_minirt *minirt);
void	ft_keyhook(void *param);

//init.c
void		init_minirt(t_minirt *minirt);
t_material	init_material(void);

//error & cleanup
void	exit_error(t_minirt *minirt, const char *msg);
void	cleanup(t_minirt *minirt);

#endif
