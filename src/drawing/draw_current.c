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
			ray = ray_for_pixel(minirt, c, x, y);
			color = color_at(minirt, ray);
			color_raw = colour_unitrgb_hex(color, 1);
			mlx_put_pixel(minirt->img, x, y, color_raw);
			y++;
		}
		x++;
	}
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
	t_matrix4	r;
	t_matrix4	first_term;
	t_matrix4	second_term;
	t_matrix4	third_term;

	k = construct_matrix(rotation_axis);
	// print_matrix(k, "k", 4);
	first_term = identity();
	// print_matrix(i, "i", 4);
	second_term = scalar_multiply_matrix(k, sin(rotation_angle));
	// print_matrix(sin_k, "sin_k", 4);
	k2 = multiply_mtrx_by_mtrx(k, k);
	// print_matrix(k2, "k2", 4);
	third_term = scalar_multiply_matrix(k2, 1 - cos(rotation_angle));
	// print_matrix(one_minus_neg_cos_k2, "one_minus_neg_cos_k2", 4);
	r = addition_matrix(addition_matrix(first_term, second_term), third_term);
	// print_matrix(r, "r", 4);
	return (r);
}

t_matrix4	cylinder_scale(t_scene_obj *obj)
{
	t_matrix4	res;

	res = scaling(obj->dia / 2.0, obj->height, obj->dia / 2.0);
	return (res);
}

t_matrix4	cylinder_rotation(t_scene_obj *obj)
{
	t_tuple		default_axis;
	t_tuple		target_axis;
	t_tuple		rotation_axis;
	float		rotation_angle;
	t_matrix4	r;

	default_axis = create_vector(0, 1, 0);
	// printf("default axis\n");
	// print_tuple(default_axis);
	target_axis = normalize_tuple(create_vector(obj->ox, obj->oy, obj->oz));
	// printf("target axis\n");
	// print_tuple(target_axis);
	rotation_axis = cross_tuple(default_axis, target_axis);
	if (magnitude_tuple(rotation_axis) < 1e-9f)
		return (identity());
	rotation_axis = normalize_tuple(rotation_axis);
	// printf("rotation axis\n");
	// print_tuple(rotation_axis);
	rotation_angle = acos(dot_tuple(default_axis, target_axis));
	// printf("angle %f\n", rotation_angle);
	r = rodrigues_formula(rotation_axis, rotation_angle);
	return (r);
}

t_matrix4	plane_rotation(t_scene_obj *obj)
{
	return(cylinder_rotation(obj));
}

t_matrix4	sphere_transformation_mtrx(t_scene_obj *obj)
{
	t_matrix4	res;
	t_matrix4	scale;
	t_matrix4	translate;

	scale = scaling(obj->dia / 2.0, obj->dia / 2.0, obj->dia / 2.0);
	translate = translation(obj->cx, obj->cy, obj->cz);
	res = multiply_mtrx_by_mtrx(translate, scale);
	return (res);
}

t_matrix4	plane_transformation_mtrx(t_scene_obj *obj)
{
	t_matrix4	res;
	t_matrix4	rotate;
	t_matrix4	translate;

	rotate = plane_rotation(obj);
	translate = translation(obj->cx, obj->cy, obj->cz);
	res = multiply_mtrx_by_mtrx(translate, rotate);
	return (res);
}

t_matrix4	cylinder_transformation_mtrx(t_scene_obj *obj)
{
	t_matrix4	res;
	t_matrix4	rotate;
	t_matrix4	scale;
	t_matrix4	translate;

	scale = cylinder_scale(obj);
	rotate = cylinder_rotation(obj);
	translate = translation(obj->cx, obj->cy, obj->cz);
	res = multiply_mtrx_by_mtrx(translate, multiply_mtrx_by_mtrx(rotate, scale));
	return (res);
}

t_matrix4	generate_transformation_mtrx(t_minirt *minirt, t_scene_obj *obj)
{
	t_matrix4	res;

	matrix_fill_zero(&res);
	if (obj->type == SPHERE)
		res = sphere_transformation_mtrx(obj);
	else if (obj->type == PLANE)
		res = plane_transformation_mtrx(obj);
	else if (obj->type == CYLINDER)
		res = cylinder_transformation_mtrx(obj);
	else
		exit_error(minirt, SHAPE);
	return (res);
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
		obj->mat = init_material();
		color_convert(obj);
		temp = temp->next;
		i++;
	}
}

void	render_world(t_minirt *minirt)
{
	init_objects(minirt);
	init_camera(minirt);
	draw_current_thing(minirt, &minirt->world->cam_s);
}

