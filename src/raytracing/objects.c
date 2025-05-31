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

t_sphere	sphere(t_minirt *minirt)
{
	t_sphere	s;

	s.center = create_point(0, 0, 0);
	s.radius = 1.0;
	s.transform = identity(minirt);
	return (s);
}
