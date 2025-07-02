#include "minirt.h"

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
	t_matrix4	rot;
	t_matrix4	scale;
	t_matrix4	translate;

	scale = scaling(obj->dia / 2.0, obj->height, obj->dia / 2.0);
	rot = cylinder_rotation(obj);
	translate = translation(obj->cx, obj->cy, obj->cz);
	res = multiply_mtrx_by_mtrx(translate, multiply_mtrx_by_mtrx(rot, scale));
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
