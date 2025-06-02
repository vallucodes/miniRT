#include "minirt.h"

void	set_colors(t_minirt *minirt)
{
	minirt->map->background = 0xFFC067BB;
	minirt->map->colored = 0xFF0000FF;
}

void	init_minirt(t_minirt *minirt)
{
	t_map *map;

	init_arena(minirt);
	minirt->map = arena_alloc(minirt->arena, sizeof(t_map), alignof(t_map));
	// if (!minirt->map)
		// exit_error();
	set_colors(minirt);
	// minirt->mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	// // if (!minirt->mlx)
	// 	// exit_error(minirt.map, NULL, 0, mlx_strerror(mlx_errno));
	// minirt->img = mlx_new_image(minirt->mlx, WIDTH, HEIGHT);
	// if (!minirt->img || (mlx_image_to_window(minirt->mlx, minirt->img, 0, 0) < 0))
	// {
	// 	mlx_close_window(minirt->mlx);
	// 	// exit_error(minirt.map, NULL, 0, mlx_strerror(mlx_errno));
	// }
}
