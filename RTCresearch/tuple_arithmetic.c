#include "tuple.h"

/*bool	tuples_are_equal(t_tuple t1, t_tuple t2)
{
	char	i;

	i = 0;
	while (i < 4)
	{
		if (!floats_are_equal(t1[i], t2[i]))
			return false;
		i++;
	}
	return true;
}*/

/**
 * @brief Adds two t_tuple objects. 
 * @param [in] l: left side of the expression. 
 * @param [in] r: right side of the expression. 
 * @return summed t_tuple. 
 */
t_tuple tuple_add(t_tuple l, t_tuple r)
{
	t_tuple sum;

	sum = tuple_init(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
	return sum;
}

/**
 * @brief Subtracts two t_tuple objects. 
 * @param [in] l: left side of the expression. 
 * @param [in] r: right side of the expression. 
 * @return differenced t_tuple. 
 */
t_tuple tuple_sub(t_tuple l, t_tuple r)
{
	t_tuple diff;

	diff = tuple_init(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
	return diff;
}

/**
 * @brief Negated t_tuple. 
 * @param [in] tuple: t_tuple to negate. 
 * @return negated t_tuple. 
 */
t_tuple tuple_neg(t_tuple tuple)
{
	t_tuple neg;

	neg = tuple_init(0 - tuple.x, 0 - tuple.y, 0 - tuple.z, 0 - tuple.w);
	return neg;
}

/**
 * @brief Takes the dot product of two t_tuple objects. 
 * @details Effectively the difference in orientation of the vectors. 
 * @param [in] l: left side of the expression. 
 * @param [in] r: right side of the expression. 
 * @return double: dot product. 
 * @note Depending on use, may need a check for whether tuple is a point. 
 */
double	tuple_dot(t_tuple l, t_tuple r)
{
	double	dot;

	dot = (l.x * r.x + l.y * r.y + l.z * r.z);
	return dot;
}

/**
 * @brief Takes the cross product of two t_tuple objects. 
 * @details Returns a vector perpendicluar to the original vectors. 
 * @param [in] l: left side of the expression. 
 * @param [in] r: right side of the expression. 
 * @return t_tuple: cross product. 
 * @note Depending on use, may need a check for whether tuple is a point. 
 */
t_tuple	tuple_cross(t_tuple l, t_tuple r)
{
	t_tuple	cross;

	cross = tuple_init(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x, 0.0);
	return cross;
}