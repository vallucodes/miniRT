#include "minirt.h"

t_ray	ray_for_pixel(t_minirt *minirt, t_camera *c, int px, int py)
{
	float	xoffset;
	float	yoffset;
	float	world_x;
	float	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;
	bool	success;

	xoffset = (px + 0.5) * c->pixel_size;
	yoffset = (py + 0.5) * c->pixel_size;

	world_x = c->half_width - xoffset;
	world_y = c->half_height - yoffset;

	pixel = multiply_mtrx_by_tuple(inverse_matrix(c->transform, &success),
									create_point(world_x, world_y, -1));
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

static void	init_objects(t_minirt *minirt)
{
	int			i;
	t_list		*temp;
	t_scene_obj	*obj;

	temp = minirt->world->objects;
	i = 0;
	while(i < minirt->world->obj_count)
	{
		obj = (t_scene_obj *)temp->content;
		obj->id = i;
		if (obj->type == CYLINDER)
		{
			obj->min = -0.5;
			obj->max = 0.5;
			obj->closed = true;
		}
		obj->transform = generate_transformation_mtrx(minirt, obj);
		obj->mat = init_material(minirt->world->amb_s.ratio);
		color_convert(obj);
		temp = temp->next;
		i++;
	}
}

void	render_world(t_minirt *minirt)
{
	init_objects(minirt);
	init_camera(minirt);
	set_pixel_color(minirt);
}

