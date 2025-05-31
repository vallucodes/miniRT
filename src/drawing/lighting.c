#include "minirt.h"

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