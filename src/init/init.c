#include "minirt.h"

/**
 * @brief Setup viewport 2D size
 * @todo FOV will eventually come from .rt file in submitted project
 */
// void	init_vp_attributes(t_minirt *minirt)
// {
// 	minirt->vp->fov = M_PI / 2;
// 	minirt->vp->aspect_ratio = (float)WIDTH / (float)HEIGHT;
// 	minirt->vp->vp_h = 2.0f * tan(minirt->vp->fov / 2);
// 	minirt->vp->vp_w = minirt->vp->aspect_ratio * minirt->vp->vp_h;
// }

void	init_minirt(t_minirt *minirt)
{
	minirt->world = NULL;
	minirt->img = NULL;
	minirt->mlx = NULL;
	minirt->vp = NULL;
	minirt->vp = malloc(sizeof(t_vp));
	if (!minirt->vp)
		exit_error(minirt, MALLOC);
	minirt->mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!minirt->mlx)
		exit_error(minirt, mlx_strerror(mlx_errno));
	minirt->img = mlx_new_image(minirt->mlx, WIDTH, HEIGHT);
	if (!minirt->img || (mlx_image_to_window(minirt->mlx, minirt->img, 0, 0) < 0))
		exit_error(minirt, mlx_strerror(mlx_errno));
	// init_vp_attributes(minirt);
}

/**
 * @brief Return t_material initialised with default values.
 * @note Default colour is 255,50,255 bluey/pinky/purpley type thing, for now.
 */
t_material	init_material(void)
{
	t_material	new;

	// new.col = color(1, 1, 1);
	new.ambient = amb_default;
	new.diffuse = dif_default;
	new.specular = spec_default;
	new.shininess = shine_default;
	return (new);
}
