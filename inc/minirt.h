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

typedef struct s_minirt t_minirt;

//Project includes.
# include "memory_arena.h"
# include "parsing.h"
# include "raytracing.h"
# include "utils.h"

typedef enum e_exit
{
	SUCCESS,
	FAIL,
}	t_exit;

typedef struct s_map
{
	uint32_t	background;
	uint32_t	colored;
}		t_map;

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
	t_arena		*arena;
	t_map		*map;
	t_vp		*vp;
	mlx_image_t	*img;
	mlx_t		*mlx;
}		t_minirt;

void	reset_background(t_minirt *minirt);
void	draw_current_thing(t_minirt *minirt);
void	draw_hook(void *param);
void	draw_circle(t_minirt *minirt);

void	init_minirt(t_minirt *minirt);

#endif
