#include "minirt.h"

void	draw_current_thing(t_minirt *minirt, t_camera *c)
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
			ray = ray_for_pixel(c, x, y);
			color = color_at(minirt, ray);
			color_raw = colour_unitrgb_hex(color, 1);
			mlx_put_pixel(minirt->img, x, y, color_raw);
			y++;
		}
		x++;
	}
}

static void	init_light(t_minirt *minirt)
{
	minirt->world->lig_s = init_point_light(create_point(minirt->world->lig_s.cx, minirt->world->lig_s.cy, minirt->world->lig_s.cz),
											color(minirt->world->lig_s.col.r, minirt->world->lig_s.col.g, minirt->world->lig_s.col.b),
											minirt->world->lig_s.ratio);
}

static void	init_objects(t_minirt *minirt)
{
	int	i;
	t_list	*temp;
	t_scene_obj *obj;

	temp = minirt->world->objects;
	obj = (t_scene_obj *)temp->content;
	i = 0;
	while(i < minirt->world->obj_count)
	{
		if (i == 0)
			obj->transform = translation(4, 2, 0);
		else if (i == 1)
			obj->transform = multiply_mtrx_by_mtrx(scaling(0.5, 0.5, 0.5), translation(-6, -4, 0));
		else if (i == 2)
			obj->transform = scaling(1.7, 0.5, 1.2);
		obj->mat = init_material();
		color_convert(obj);
		temp = temp->next;
		if (temp != NULL)
			obj = (t_scene_obj *)temp->content;
		else
			break ;
		i++;
	}
}

void	render_world(t_minirt *minirt)
{

	init_light(minirt);
	init_objects(minirt);
	init_camera(minirt);
	draw_current_thing(minirt, &minirt->world->cam_s);
}
