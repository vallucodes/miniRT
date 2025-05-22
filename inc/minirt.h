#ifndef MINIRT_H
# define MINIRT_H

//System includes.
# include <math.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

//42 specific includes.
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"

//Project includes.
# include "parsing.h"
# include "raytracing.h"
# include "utils.h"

typedef struct s_map
{
	uint32_t	background;
	uint32_t	colored;
}		t_map;

typedef struct s_minirt
{
	t_map		*map;
	mlx_image_t	*img;
	mlx_t		*mlx;
}		t_minirt;

void	reset_background(t_minirt *minirt);
void	draw_current_thing(t_minirt *minirt);
void	draw_hook(void *param);
void	draw_circle(t_minirt *minirt);

#endif
