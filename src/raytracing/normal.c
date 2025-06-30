#include "minirt.h"

/**
 * @brief Return the sphere object normal for a given local [point]
 */
t_tuple	normal_at_sphere(t_tuple point)
{
	t_tuple	object_normal;

	object_normal = substraction_tuples(point, create_point(0, 0, 0));
	return (object_normal);
}

/**
 * @brief Return the plane normal for a given local [point]
 * @details The normal at any point of plane will be perpendicular to plane
 * @todo only having point as a param to mirror other functions, may remove
 */
t_tuple	normal_at_plane(t_tuple point)
{
	(void)point;
	return (create_vector(0, 1, 0));
}

/**
 * @brief Return the normal of a cylinder for a given local [point] 
 */
t_tuple	normal_at_cylinder(t_scene_obj *cylinder, t_tuple point)
{
	float	dist;

	dist = (point.x * point.x) + (point.z * point.z);
	if (dist < 1 && point.y >= cylinder->max - EPSILON)
		return (create_vector(0, 1, 0));
	else if (dist < 1 && point.y <= cylinder->min + EPSILON)
		return (create_vector(0, -1, 0));
	return (create_vector(point.x, 0, point.z));
}

/**
 * @brief Return the global normal at a given [point] for a given [obj]ect
 * @details Convert point to object space > find appropriate object normal
 * 			> convert object normal to global space and return normalised
 */
t_tuple	normal_at(t_minirt *minirt, t_scene_obj *obj, t_tuple point)
{
	t_tuple		local_point;
	t_tuple		local_normal;
	t_tuple		world_normal;
	t_matrix4	inverse;
	t_matrix4	tmp;
	bool		success;

	inverse = inverse_matrix(obj->transform, &success);
	if (!success)
		exit_error(minirt, INVERSE_MATRIX);
	local_point = multiply_mtrx_by_tuple(inverse, point);
	if (obj->type == PLANE)
		local_normal = normal_at_plane(point);
	else if (obj->type == SPHERE)
		local_normal = normal_at_sphere(local_point);
	else if (obj->type == CYLINDER)
		local_normal = normal_at_cylinder(obj, local_point);
	tmp = transpose_matrix(inverse);
	world_normal = multiply_mtrx_by_tuple(tmp, local_normal);
	world_normal.w = 0;
	return (normalize_tuple(world_normal));
}
