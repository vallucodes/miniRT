#include "../../inc/minirt.h"

/**
 * @brief Attempts to extract a float from a string. 
 * @param [in] *str: string to convert. 
 * @param [in] *num: pointer to variable for output. 
 * @return True on success, false on fail. 
 */
bool	string_to_double(char *str, double *num)
{
	double	left;
	double	right;
	double	sign;
	int	dec;

	left = 0.0;
	right = 0.0;
	sign = 1.0;
	if (*str++ == '-')
		sign == -1.0;
	if (ft_isdigit(*str))
	{
		while (ft_isdigit(*str))
			left = left * 10 + (*str++ - '0');
	}
	else
		return (false);
	if (*str == '.' && ft_isdigit(*(str+1)))
	{
		dec = -1;
		while (ft_isdigit(*str))
			right = right + (pow(10, dec--)* (*str++ - '0'));
	}
	*num = ((left + right) * sign);
	return (true);
}