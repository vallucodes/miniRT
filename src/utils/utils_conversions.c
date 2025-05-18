#include "../../inc/minirt.h"

/**
 * @brief Attempts to extract a float from a string. 
 * @param [in] *str: string to convert. 
 * @param [in] *num: pointer to variable for output. 
 * @return True on success, false on fail. 
 */
bool	string_to_double(char *str, double *num)
{
	double	tmp[3];
	int		dec;

	ft_memset(&tmp, 0, 3 * sizeof(double));
	tmp[2] = 1.0;
	if (*str == '-')
	{
		tmp[2] = -1.0;
		str++;
	}
	if (ft_isdigit(*str))
	{
		while (ft_isdigit(*str))
			tmp[0] = tmp[0] * 10 + (*str++ - '0');
	}
	else
		return (false);
	if (*str == '.' && ft_isdigit(*(str++ + 1)))
	{
		dec = -1;
		while (ft_isdigit(*str))
			tmp[1] = tmp[1] + (pow(10, dec--) * (*str++ - '0'));
	}
	*num = ((tmp[0] + tmp[1]) * tmp[2]);
	return (true);
}
