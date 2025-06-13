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
	t_light	*light;

	light = &minirt->world->lig_s;
	*light = init_point_light(create_point(light->cx, light->cy, light->cz),
				color(light->col.r, light->col.g, light->col.b), light->ratio);
}

t_matrix4	construct_matrix(t_tuple rotation_axis)
{
	t_matrix4	m;

	matrix_fill_zero(&m);
	m.m[0][1] = -rotation_axis.z;
	m.m[0][2] = rotation_axis.y;
	m.m[1][0] = rotation_axis.z;
	m.m[1][2] = -rotation_axis.x;
	m.m[2][0] = -rotation_axis.y;
	m.m[2][1] = rotation_axis.x;
	return (m);
}

t_matrix4	rodrigues_formula(t_tuple rotation_axis, float rotation_angle)
{
	t_matrix4	k;
	t_matrix4	k2;
	t_matrix4	i;
	t_matrix4	sin_k;
	t_matrix4	one_minus_neg_cos_k2;
	t_matrix4	r;

	k = construct_matrix(rotation_axis);
	print_matrix(k, "k", 4);
	i = identity();
	print_matrix(i, "i", 4);
	sin_k = scalar_multiply_matrix(k, sin(rotation_angle));
	print_matrix(sin_k, "sin_k", 4);
	k2 = multiply_mtrx_by_mtrx(k, k);
	print_matrix(k2, "k2", 4);
	one_minus_neg_cos_k2 = scalar_multiply_matrix(k2, 1 - cos(rotation_angle));
	print_matrix(one_minus_neg_cos_k2, "one_minus_neg_cos_k2", 4);
	r = addition_matrix(addition_matrix(i, sin_k), one_minus_neg_cos_k2);
	print_matrix(r, "r", 4);
	return (r);
}


t_matrix4	cylinder_rotation(t_scene_obj *obj) //test this fucker
{
	t_tuple		default_axis;
	t_tuple		target_axis;
	t_tuple		rotation_axis;
	float		rotation_angle;
	t_matrix4	r;

	default_axis = create_vector(0, 1, 0);
	printf("default axis\n");
	print_tuple(default_axis);
	target_axis = create_vector(obj->ox, obj->oy, obj->oz);
	printf("target axis\n");
	print_tuple(target_axis);
	rotation_axis = normalize_tuple(cross_tuple(default_axis, target_axis));
	printf("rotation axis\n");
	print_tuple(rotation_axis);
	rotation_angle = acos(dot_tuple(default_axis, target_axis));
	printf("angle %f\n", rotation_angle);
	r = rodrigues_formula(rotation_axis, rotation_angle);
	return (r);
}

t_matrix4	generate_transformation_mtrx(t_minirt *minirt, t_scene_obj *obj)
{
	t_matrix4	res;
	t_matrix4	rotate;
	t_matrix4	scale;
	t_matrix4	translate;

	if (obj->type == SPHERE)
	{
		scale = scaling(obj->dia / 2.0, obj->dia / 2.0, obj->dia / 2.0);
		translate = translation(obj->cx, obj->cy, obj->cz);
		res = multiply_mtrx_by_mtrx(translate, scale);
	}
	// else if (obj->type == PLANE)
	// {
	// 	translate = translation(obj->cx, obj->cy, obj->cz);
	// }
	// else if (obj->type == CYLINDER)
	// {
	// 	rotate = cylinder_rotation(obj);
	// 	translate = translation(obj->cx, obj->cy, obj->cz);
	// }
	return (res);
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
		obj->transform = generate_transformation_mtrx(minirt, obj);
		// print_matrix(obj->transform, "transform", 4);
		// if (i == 0)
		// 	obj->transform = translation(4, 2, 0);
		// else if (i == 1)
		// 	obj->transform = multiply_mtrx_by_mtrx(scaling(0.5, 0.5, 0.5), translation(-6, -4, 0));
		// else if (i == 2)
		// 	obj->transform = scaling(1.7, 0.5, 1.2);
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
