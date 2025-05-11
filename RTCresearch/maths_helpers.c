#include "tuple.h"

/**
	* @brief Checks if two doubles are equal within a defined epsilon. 
	* @param [in] n1, n2: doubles to compare. 
	* @return true or false. 
*/
bool	floats_are_equal(double n1, double n2)
{
	if (fabs(n1 - n2) < epsilon)
		return true;
	return false;
}