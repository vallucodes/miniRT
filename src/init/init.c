#include "minirt.h"

void	set_colors(t_minirt *minirt)
{
	minirt->map->background = 0xFF8800FF;
	minirt->map->colored = 0xFF0000FF;
}

/**
 * @brief Setup viewport 2D size
 * @attention FOV will eventually come from .rt file in submitted project
 */
void	init_vp_attributes(t_minirt *minirt)
{
	minirt->vp->fov = M_PI_2;
	minirt->vp->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	minirt->vp->vp_h = 2.0f * tan(minirt->vp->fov / 2);
	minirt->vp->vp_w = minirt->vp->aspect_ratio * minirt->vp->vp_h;
}

void	init_minirt(t_minirt *minirt)
{
	t_map *map;

	init_arena(minirt);
	minirt->map = arena_alloc(minirt->arena, sizeof(t_map), alignof(t_map));
	// if (!minirt->map)
		// exit_error();
	set_colors(minirt);
	minirt->vp = arena_alloc(minirt->arena, sizeof(t_vp), alignof(t_vp));
	
	minirt->mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	// if (!minirt->mlx)
		// exit_error(minirt.map, NULL, 0, mlx_strerror(mlx_errno));
	minirt->img = mlx_new_image(minirt->mlx, WIDTH, HEIGHT);
	if (!minirt->img || (mlx_image_to_window(minirt->mlx, minirt->img, 0, 0) < 0))
	{
		mlx_close_window(minirt->mlx);
		// exit_error(minirt.map, NULL, 0, mlx_strerror(mlx_errno));
	}
	init_vp_attributes(minirt);
}

/**
 * @brief Return t_material initialised with default values. 
 */
t_material	init_material(void)
{
	t_material	new;

	new.col = color(1, 1, 1);
	new.ambient = amb_default;
	new.diffuse = dif_default;
	new.specular = spec_default;
	new.shininess = shine_default;
	return (new);
}
