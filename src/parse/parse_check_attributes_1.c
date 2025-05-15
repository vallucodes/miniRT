#include "../../inc/minirt.h"

/**
 * @brief Checks a given ratio is within the range [0.0,1.0].  
 * @param [in] *str: the string containing the ratio. 
 * @param [in] *num: pointer to where the number should be stored. 
 */
bool	parse_check_ratio(char *str, float *num)
{
	double	*tmp;

	if (!str_to_double(str, &tmp))
		return (false);
	if (*tmp < 0.0 || *tmp > 1.0)
		return (false);
	*num = *tmp;
	return (true);
}

/**
 * @brief Checks a given RGB tuple is within the range [0,255][0,255][0,255].  
 * @param [in] *str: the string containing the values. 
 * @param [in] *R, G or B: pointer to where the values should be stored. 
 */
bool	parse_check_rgb(char *str, t_rgb *r, t_rgb *g, t_rgb *b)
{
	char	**tuple;
	int		tmp;

	tuple = ft_split(str, ',');
	tmp = ft_atoi(tuple[0]);
	if (tmp < RGB_MIN || tmp > RGB_MAX)
		return (false);
	*r = (t_rgb)tmp;
	tmp = ft_atoi(tuple[1]);
	if (tmp < RGB_MIN || tmp > RGB_MAX)
		return (false);
	*g = (t_rgb)tmp;
	tmp = ft_atoi(tuple[2]);
	if (tmp < RGB_MIN || tmp > RGB_MAX)
		return (false);
	*b = (t_rgb)tmp;
	free_matrix(tuple);
	return (true);
}

/**
 * @brief Checks a given coordinate tuple is valid. 
 * @param [in] *str: the string containing the coordinates. 
 * @param [in] *cx, xy or xz: pointer to where the values should be stored. 
 */
bool	parse_check_coords(char *str, float *cx, float *cy, float *cz)
{
	char	**tuple;
	float	*tmp;

	tuple = ft_split(str, ',');
	if (!string_to_double(tuple[0], &tmp))
		return (false);
	*cx = *tmp;
	if (!string_to_double(tuple[1], &tmp))
		return (false);
	*cy = *tmp;
	if (!string_to_double(tuple[2], &tmp))
		return (false);
	*cz = *tmp;
	free_matrix(tuple);
	return (true);
}

/**
 * @brief Checks given orientation tuple is within range [-1,1][-1,1][-1,1].  
 * @param [in] *str: the string containing the orientation coordinates. 
 * @param [in] *ox, oy or oz: pointer to where the values should be stored. 
 */
bool	parse_check_orient(char *str, float *ox, float *oy, float *oz)
{
	char	**tuple;
	float	*tmp;

	tuple = ft_split(str, ',');
	if (!string_to_double(tuple[0], &tmp) || *tmp < -1.0 || *tmp > 1.0)
		return (false);
	*ox = *tmp;
	if (!string_to_double(tuple[1], &tmp) || *tmp < -1.0 || *tmp > 1.0)
		return (false);
	*oy = *tmp;
	if (!string_to_double(tuple[2], &tmp) || *tmp < -1.0 || *tmp > 1.0)
		return (false);
	*oz = *tmp;
	free_matrix(tuple);
	return (true);
}

/**
 * @brief Checks a given field of view is within the range [0,180].  
 * @param [in] *str: the string containing the fov. 
 * @param [in] *num: pointer to where the number should be stored. 
 */
bool	parse_check_fov(char *str, unsigned char *num)
{
	int	tmp;

	tmp = ft_atoi(*num);
	if (tmp < FOV_MIN || tmp > FOV_MAX)
		return (false);
	*num = (unsigned char)tmp;
	return (true);
}
