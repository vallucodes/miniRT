#include "minirt.h"

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
	first_term = identity();
	second_term = scalar_multiply_matrix(k, sin(rotation_angle));
	k2 = multiply_mtrx_by_mtrx(k, k);
	third_term = scalar_multiply_matrix(k2, 1 - cos(rotation_angle));
	r = addition_matrix(addition_matrix(first_term, second_term), third_term);
	return (r);
}

t_matrix4	cylinder_rotation(t_scene_obj *obj)
{
	t_tuple		default_axis;
	t_tuple		target_axis;
	t_tuple		rotation_axis;
	float		rotation_angle;
	t_matrix4	r;

	default_axis = create_vector(0, 1, 0);
	target_axis = normalize_tuple(create_vector(obj->ox, obj->oy, obj->oz));
	rotation_axis = cross_tuple(default_axis, target_axis);
	if (magnitude_tuple(rotation_axis) < 1e-9f)
		return (identity());
	rotation_axis = normalize_tuple(rotation_axis);
	rotation_angle = acos(dot_tuple(default_axis, target_axis));
	r = rodrigues_formula(rotation_axis, rotation_angle);
	return (r);
}

t_matrix4	plane_rotation(t_scene_obj *obj)
{
	return(cylinder_rotation(obj));
}
