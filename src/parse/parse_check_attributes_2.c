#include "../../inc/minirt.h"

/**
 * @brief Checks a given geometry is a positive number.  
 * @param [in] *str: the string containing the size. 
 * @param [in] *num: pointer to where the number should be stored. 
 */
bool	parse_check_geometry(char *str, unsigned char *num)
{
	float	*tmp;

	if (!string_to_double(str, &tmp) || *tmp < 0.0)
		return (false);
	*num = *tmp;
	return (true);
}
