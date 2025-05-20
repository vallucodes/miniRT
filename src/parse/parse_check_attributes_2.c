#include "../../inc/minirt.h"

/**
 * @brief Checks a given geometry is a positive number.  
 * @param [in] *str: the string containing the size. 
 * @param [in] *num: pointer to where the number should be stored. 
 */
bool	parse_check_geometry(char *str, float *num)
{
	double	tmp;

	if (!string_to_double(str, &tmp) || tmp < 0.0)
	{
		put_error(ERR_GEO);
		return (false);
	}
	*num = tmp;
	return (true);
}
