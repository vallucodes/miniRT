#include "minirt.h"

void	draw_current_thing(t_minirt *minirt, t_camera *c)
{
	size_t		x;
	size_t		y;
	t_color		color;
	uint32_t	color_raw;
	t_ray		ray;

	x = 0;
	while (x < 1)
	{
		y = 0;
		while (y < 1)
		{
			ray = ray_for_pixel(minirt, c, x, y);
			print_ray(ray);
			color = color_at(minirt, ray);
			print_colour(color);
			color_raw = colour_unitrgb_hex(color, 1);
			mlx_put_pixel(minirt->img, x, y, color_raw);
			y++;
		}
		x++;
	}
}

void	render_world(t_minirt *minirt)
{
	minirt->world->lig_s = init_point_light(create_point(-10, 10, -10), color(1, 1, 1), 1);

	t_list	*temp = minirt->world->objects;
	t_scene_obj *obj = (t_scene_obj *)temp->content;

	obj->transform = translation(2, 0, 0);
	obj->mat = init_material();
	obj->mat.ambient = 0.1;
	obj->mat.diffuse = 0.7;
	obj->mat.specular = 0.2;
	obj->mat.col.r = 0.8;
	obj->mat.col.g = 1;
	obj->mat.col.b = 0.6;

	temp = temp->next;
	obj = (t_scene_obj *)temp->content;
	obj->transform = scaling(0.5, 0.5, 0.5);
	obj->mat = init_material();
	obj->mat.ambient = 0.1;
	obj->mat.diffuse = 0.9;
	obj->mat.specular = 0.9;
	obj->mat.col.r = 1;
	obj->mat.col.g = 1;
	obj->mat.col.b = 1;

	init_camera(minirt);
	t_tuple	from = create_point(0, 0, -5);
	t_tuple	to = create_point(0, 0, 0);
	t_tuple	up = create_vector(0, 1, 0);
	minirt->world->cam_s.transform = view_transform(from, to, up);
	// print_matrix(minirt->world->cam_s.transform, "camera", 4);
	draw_current_thing(minirt, &minirt->world->cam_s);
}
