#include "tuple.h"

/**
 * @brief Creates a t_tuple object. 
 * @param [in] x, y, z, w: doubles to fill the tuple with. 
 * @return filled t_tuple. 
 */
t_tuple	tuple_init(double x, double y, double z, double w)
{
	t_tuple tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	tmp.w = w;
	return tmp;
}

/**
 * @brief Creates a t_tuple object from a vector. 
 * @param [in] *vec: array of doubles to transform into a tuple. 
 * @return filled t_tuple. 
 */
t_tuple	tuple_from_vector(double *vec)
{
	t_tuple	tmp;

	tmp = tuple_init(vec[0], vec[1], vec[2], 0.0);
	return tmp;
}

/**
 * @brief Creates a t_tuple object from a point. 
 * @param [in] *point: array of doubles to transform into a tuple. 
 * @return filled  t_tuple. 
 */
t_tuple	tuple_from_point(double *point)
{
	t_tuple	tmp;

	tmp = tuple_init(point[0], point[1], point[2], 1.0);
	return tmp;
}