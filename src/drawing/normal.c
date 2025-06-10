#include "minirt.h"

/**
 * @brief Return the sphere object normal for a given [point]
 */
t_tuple	normal_at_sphere(t_tuple point)
{
	t_tuple	object_normal;
	//float **inv_transform;

	//Find point in object space
	//inv_transform = inverse_matrix(minirt, s.transform, 4);
	//print_matrix(inv_transform, "s1 inverted transform ", 4);
	//res = multiply_mtrx_by_tuple(inv_transform, p, 4);
	//printf("object_point\n");
	//print_tuple(res);

	//Find normal vector while in object space
	object_normal = substraction_tuples(point, create_point(0, 0, 0));
	//printf("object_normal\n");
	//print_tuple(res);

	//Convert object space to world space, set w to 0 and return normalised
	//res = multiply_mtrx_by_tuple(transpose_matrix(minirt, inv_transform, 4), res, 4);
	//res.w = 0;
	return (object_normal);
}

/**
 * @brief Return the global normal at a given [point] for a given [obj]ect
 * @details Convert point to object space > find appropriate object normal
 * 			> convert object normal to global space and return normalised
 */
t_tuple	normal_at(t_minirt *minirt, t_scene_obj *obj, t_tuple point)
{
	t_tuple	local_point;
	t_tuple	local_normal;
	t_tuple	world_normal;
	float	**inverse;
	float	**tmp;

	inverse = inverse_matrix(minirt, obj->transform, 4);
	//print_matrix(obj->transform, "obj.transform", 4);
	//print_matrix(inverse, "Inverse obj.transform", 4);

	local_point = multiply_mtrx_by_tuple(inverse, point, 4);
	//rintf("local_point\n");
	//print_tuple(local_point);
	
	if (obj->type == PLANE)
	{
		/* plane */
	}
	else if (obj->type == SPHERE)
	{
		//printf("local_normal passed to sphere function\n");
		local_normal = normal_at_sphere(local_point);
	}
	else if (obj->type == CYLINDER)
	{
		/* cylinder */
	}
	//printf("local_normal\n");
	//print_tuple(local_normal);
	
	tmp = transpose_matrix(minirt, inverse, 4);
	//print_matrix(tmp, "transpose of invert obj.transform", 4);
	world_normal = multiply_mtrx_by_tuple(tmp, local_normal, 4);
	world_normal.w = 0;
	
	//printf("world_normal\n");
	//print_tuple(world_normal);
	return (normalize_tuple(world_normal));
}
