#include "minirt.h"

/**
 * @brief Find the normal vector at the given location of the given sphere
 * @returns Normal vector
 * @details Sphere needs to be in object space if its origin not at world origin
 * 			Normal calculation needs to be done in object space
 * 			Result needs to be converted to world space
 */
t_tuple	normal_at_sphere(t_minirt *m, t_sphere s, t_tuple p)
{
	t_tuple	res;
	float **inv_transform;

	inv_transform = inverse_matrix(m, s.transform, 4);
	print_matrix(inv_transform, "s1 inverted transform ", 4);

	res = multiply_mtrx_by_tuple(inv_transform, p, 4);
	printf("object_point");
	print_tuple(res);

	res = substraction_tuples(res, create_point(0,0,0));
	printf("object_normal");
	print_tuple(res);

	res = multiply_mtrx_by_tuple(transpose_matrix(m, inv_transform, 4), p, 4);
	res.w = 0;
	return (res);
}

/**
 * @brief Returns a vector the result of reflecting ray in about vector normal 
 * @attention t_ray as in seems more useful, however it could be easily
 * 			adapted to t_tuple 
 */
t_tuple	reflect(t_ray in_ray, t_tuple normal)
{
	t_tuple	in_tup;
	t_tuple	out_tup;
	float	tmp;
	
	in_tup = in_ray.dir;
	print_tuple(in_tup);

	tmp = 2 * dot_tuple(in_tup, normal);
	printf("tmp: %f\n", tmp);

	out_tup = scalar_multiply_tuple(normal, tmp);
	print_tuple(out_tup);

	out_tup = substraction_tuples(in_tup, out_tup);

	return (out_tup);
}

/**
 * @brief Shades objects
 */
void	lighting()
{}
