#include "../../inc/minirt.h"

/**
 * @brief Checks a given ratio is within the range [0.0,1.0].  
 * @param [in] *str
 * @param [in] *num: pointer to where the number should be stored. 
 * @return True if ratio was valid and set 
 */
bool	parse_check_ratio(char *str, float *num)
{
	double	tmp;

	tmp = string_to_double(str);
	if (tmp < 0.0 || tmp > 1.0)
	{
		put_error(ERR_RAT);
		return (false);
	}
	*num = tmp;
	return (true);
}

/**
 * @brief Checks a given RGB tuple is within the range [0,255][0,255][0,255].  
 * @param [in] *str: string containing comma separated values. 
 * @param [in] *R, G or B: pointer to where the values should be stored. 
 * @return True if RGB values were valid and set 
 * @details Allocates memory to **tuple via ft_split(). 
 */
bool	parse_check_rgb(char *str, int *r, int *g, int *b)
{
	char	**tuple;
	int		tmp;

	tuple = ft_split(str, ',');
	if (fun_words(str, ",") != 3)
		return (free_helper(NULL, tuple, NULL, ERR_RGB));
	tmp = strict_atoi(tuple[0]);
	if (tmp < RGB_MIN || tmp > RGB_MAX)
		return (free_helper(NULL, tuple, NULL, ERR_RGB));
	*r = tmp;
	tmp = strict_atoi(tuple[1]);
	if (tmp < RGB_MIN || tmp > RGB_MAX)
		return (free_helper(NULL, tuple, NULL, ERR_RGB));
	*g = tmp;
	tmp = strict_atoi(tuple[2]);
	if (tmp < RGB_MIN || tmp > RGB_MAX)
		return (free_helper(NULL, tuple, NULL, ERR_RGB));
	*b = tmp;
	free_matrix(tuple);
	return (true);
}

/**
 * @brief Checks a given coordinate tuple is valid. 
 * @param [in] *str: string containing comma separated coordinates. 
 * @param [in] *cx, xy or xz: pointer to where the values should be stored. 
 * @return True if coordinate values were valid and set 
 * @details Allocates memory to **tuple via ft_split(). 
 */
bool	parse_check_coords(char *str, float *cx, float *cy, float *cz)
{
	char	**tuple;
	double	tmp;

	tuple = ft_split(str, ',');
	if (fun_words(str, ",") != 3)
		return (free_helper(NULL, tuple, NULL, ERR_CO));
	tmp = string_to_double(tuple[0]);
	if (tmp < CO_MIN || tmp > CO_MAX)
		return (free_helper(NULL, tuple, NULL, ERR_CO));
	*cx = tmp;
	tmp = string_to_double(tuple[1]);
	if (tmp < CO_MIN || tmp > CO_MAX)
		return (free_helper(NULL, tuple, NULL, ERR_CO));
	*cy = tmp;
	tmp = string_to_double(tuple[2]);
	if (tmp < CO_MIN || tmp > CO_MAX)
		return (free_helper(NULL, tuple, NULL, ERR_CO));
	*cz = tmp;
	free_matrix(tuple);
	return (true);
}

/**
 * @brief Checks given orientation tuple is normalised and within range [-1,1]
 * @param [in] *str: string containing comma separated orientation vector. 
 * @param [in] *ox, oy or oz: pointer to where the values should be stored. 
 * @details Allocates memory to **tuple via ft_split(). 
 */
bool	parse_check_orient(char *str, float *ox, float *oy, float *oz)
{
	char	**tuple;
	double	tmp;

	tuple = ft_split(str, ',');
	if (fun_words(str, ",") != 3)
		return (free_helper(NULL, tuple, NULL, ERR_OO));
	tmp = string_to_double(tuple[0]);
	if (tmp < OR_MIN || tmp > OR_MAX)
		return (free_helper(NULL, tuple, NULL, ERR_OO));
	*ox = tmp;
	tmp = string_to_double(tuple[1]);
	if (tmp < OR_MIN || tmp > OR_MAX)
		return (free_helper(NULL, tuple, NULL, ERR_OO));
	*oy = tmp;
	tmp = string_to_double(tuple[2]);
	if (tmp < OR_MIN || tmp > OR_MAX)
		return (free_helper(NULL, tuple, NULL, ERR_OO));
	*oz = tmp;
	if (!is_equal(sqrt(fabs((*ox * *ox) + (*oy * *oy) + (*oz * *oz))), 1))
		return (free_helper(NULL, tuple, NULL, ERR_OO_NORM));
	free_matrix(tuple);
	return (true);
}

/**
 * @brief Checks a given field of view is within the range [0,180].  
 * @param [in] *str
 * @param [in] *num: pointer to where the number should be stored. 
 * @return True if FOV was valid and set 
 */
bool	parse_check_fov(char *str, unsigned char *num)
{
	int	tmp;

	tmp = strict_atoi(str);
	if (tmp < FOV_MIN || tmp > FOV_MAX)
	{
		put_error(ERR_FOV);
		return (false);
	}
	*num = (unsigned char)tmp;
	return (true);
}
