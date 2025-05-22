#include "../../inc/minirt.h"

/**
 * @brief Checks a given size geometry is a positive number.  
 * @param [in] *str 
 * @param [in] *num: pointer to where the number should be stored. 
 * @return True if size was valid and set 
 */
bool	parse_check_geometry(char *str, float *num)
{
	double	tmp;

	tmp = string_to_double(str);
	if (tmp < 0.0)
	{
		put_error(ERR_GEO);
		return (false);
	}
	*num = tmp;
	return (true);
}
