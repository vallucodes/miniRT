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
t_material	init_material(float amb_ratio)
{
	t_material	new;

	// new.col = color(1, 1, 1);
	new.ambient = amb_ratio;
	new.diffuse = DIF_DEFAULT;
	new.specular = SPEC_DEFAULT;
	new.shininess = SHINE_DEFAULT;
	return (new);
}

/**
 * @brief Set: xs.count = 0
 */
void	init_xs(t_xs *xs)
{
	xs->count = 0;
}

/**
 * @brief For i1 & i2. Set: i.t = 0, i.object = NULL
 * @todo May not be needed, check later
 */
void	init_i_to_zeroes(t_i *i1, t_i *i2)
{
	i1->t = 0;
	i1->object = NULL;
	i2->t = 0;
	i2->object = NULL;
}
/*void	init_i_to_zeroes(t_i_t *i)
{
	i->i1.t = 0;
	i->i1.object = NULL;
	i->i2.t = 0;
	i->i2.object = NULL;
}*/
