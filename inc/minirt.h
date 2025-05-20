#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"
# include <math.h> //sqrt
// # include <bool.h>
# include <stdio.h>
# include "raytracing.h"

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
