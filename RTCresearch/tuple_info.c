#include "tuple.h"
#include <math.h>


/**
 * @brief Prints the contents of a given tuple. 
 * @note Uses printf.  
 */
void	tuple_print(t_tuple tuple)
{
	printf("Tuple (x, y, z, w): %f, %f, %f, %f\n", tuple.x, tuple.y, tuple.z, tuple.w);
}

/**
 * @brief Checks if the given t_tuple is a vector. 
 * @param [in] tuple: t_tuple to check. 
 * @return bool: true if t_tuple is a vector. 
 */
bool	tuple_is_vector(t_tuple tuple)
{
	if (floats_are_equal(tuple.w, 0))
		return true;
	return false;
}

/**
 * @brief Checks if the given t_tuple is a point. 
 * @param [in] tuple: t_tuple to check. 
 * @return bool: true if t_tuple is a point. 
 */
bool	tuple_is_point(t_tuple tuple)
{
	if (floats_are_equal(tuple.w, 1))
		return true;
	return false;
}

/**
 * @brief Calculates the magnitude (length) of a given t_tuple. 
 * @param [in] tuple: t_tuple to calculate. 
 * @return double: magnitude of the given t_tuple. 
 * @note Depending on use, may need a check for whether tuple is a point. 
 */
double	tuple_magnitude(t_tuple tuple)
{
	double	mag;

	mag = sqrt((tuple.x * tuple.x) + (tuple.y * tuple.y) + (tuple.z * tuple.z));
	return mag;
}

/**
 * @brief Normalises (converts to unit vector) a given t_tuple. 
 * @param [in] tuple: t_tuple to calculate. 
 * @return t_tuple: normalised t_tuple. 
 * @note Depending on use, may need a check for whether tuple is a point. 
 */
t_tuple	tuple_normalise(t_tuple tuple)
{
	t_tuple	norm;
	double	mag;

	mag = tuple_magnitude(tuple);
	norm = tuple_init(tuple.x / mag, tuple.y / mag, tuple.z / mag, 0.0);
	return norm;
}