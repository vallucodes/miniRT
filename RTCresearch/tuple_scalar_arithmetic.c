#include "tuple.h"

/**
 * @brief Takes the product of a t_tuple object and a scalar. 
 * @param [in] l: t_tuple, left side of the expression. 
 * @param [in] fac: scalar factor, as right side of the expression. 
 * @return t_tuple: scalar product. 
 */
t_tuple tuple_mult(t_tuple l, double fac)
{
	t_tuple prod;

	prod = tuple_init(l.x * fac, l.y * fac, l.z * fac, l.w * fac);
	return prod;
}

/**
 * @brief Takes the quotient of a t_tuple object and a scalar. 
 * @param [in] l: t_tuple, left side of the expression. 
 * @param [in] div: scalar divisor, as right side of the expression. 
 * @return t_tuple: scalar quotient. 
 * @note Depending on use, may need to check for divide by zero. 
 */
t_tuple tuple_div(t_tuple l, double div)
{
	t_tuple quot;

	quot = tuple_init(l.x / div, l.y / div, l.z / div, l.w / div);
	return quot;
}