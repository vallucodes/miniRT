#include "../../inc/minirt.h"

/**
 * @brief Counts only leading digits in a string. 
 * @param [in] *str
 * @return 0 if string NULL. 
 */
static int	count_digits(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0' && ft_isdigit(str[i]))
		i++;
	return (i);
}

/**
 * @brief Attempts to extract a float from a string. 
 * @param [in] *str: string to convert. 
 * @param [in] *num: pointer to variable for output. 
 * @return True on success, false on fail. 
 * @note Allocates memory to **sides via ft_split(). 
 */
double	string_to_double(const char *str)
{
	double	parts[3];
	char 	**sides;
	int		dec;

	ft_memset(&parts, 0, 3 * sizeof(double));
	parts[0] = 1.0;
	if (str == NULL)
		return (CO_MIN - CO_MAX);
	if (*str == '-')
	{
		parts[0] = -1.0;
		str++;
	}
	sides = ft_split(str, '.');
	dec = count_digits(sides[1]) * -1;
	parts[1] = strict_atoi(sides[0]);
	if (sides[1] == NULL)
		parts[2] = 0;
	else
		parts[2] = strict_atoi(sides[1]) * pow(10, (double)dec);
	free_matrix(sides);
	if (parts[1] < 0 || parts[2] < 0)
		return (CO_MIN - CO_MAX);
	return (parts[0] * (parts[1] + parts[2]));
}

/**
 * @brief Attempts to extract an int from a string. 
 * @param [in] *nptr: string to convert. 
 * @return Positive int on success, -1 on fail. 
 * @note In current use, there are no negative ints, so if the result is
 * negative, then the conversion failed.
 * Failure occurs on any non-digit in the string, regardless of position.
 */
int	strict_atoi(const char *nptr)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	if (nptr == NULL)
		return (-1);
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		num *= 10;
		num += *nptr - 48;
		nptr++;
	}
	num = num * sign;
	if ((*nptr != '\0' && !ft_isspace(*nptr)) || num > INT_MAX || num < INT_MIN)
		return (-1);
	return ((int)num);
}
