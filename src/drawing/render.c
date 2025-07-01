#include "minirt.h"

t_ray	ray_for_pixel(t_minirt *minirt, t_camera *c, int px, int py)
{
	t_calc_vars	vars;
	t_tuple		pixel;
	t_tuple		origin;
	t_tuple		direction;
	bool		success;

	vars.xoffset = (px + 0.5) * c->pixel_size;
	vars.yoffset = (py + 0.5) * c->pixel_size;

	vars.view_port_x = c->half_width - vars.xoffset;
	vars.view_port_y = c->half_height - vars.yoffset;

	pixel = multiply_mtrx_by_tuple(inverse_matrix(c->transform, &success),
								create_point(vars.view_port_x, vars.view_port_y, -1));
	if (!success)
		exit_error(minirt, INVERSE_MATRIX);
	origin = multiply_mtrx_by_tuple(inverse_matrix(c->transform, &success),
								create_point(0, 0, 0));
	if (!success)
		exit_error(minirt, INVERSE_MATRIX);
	direction = normalize_tuple(substraction_tuples(pixel, origin));
	return (create_ray(direction, origin));
}

void	set_pixel_color(t_minirt *minirt)
{
	size_t		x;
	size_t		y;
	t_color		color;
	uint32_t	color_raw;
	t_ray		ray;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray = ray_for_pixel(minirt, &minirt->world->cam_s, x, y);
			color = color_at(minirt, ray);
			color_raw = colour_unitrgb_hex(color, 1);
			mlx_put_pixel(minirt->img, x, y, color_raw);
			y++;
		}
		x++;
	}
}

void	render_world(t_minirt *minirt)
{
	init_objects(minirt);
	init_camera(minirt);
	set_pixel_color(minirt);
}

