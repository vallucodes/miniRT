#include "../../inc/minirt.h"

/**
 * @brief Checks current character for match with optical object.
 * @param [in] *line: the current line of the scene file. 
 * @param [in] ps: t_parse. 
 * @return True if good, false otherwise.  
 */
bool	char_optical_object(char *line, t_parse ps)
{
	if (*line == 65 && ft_isspace(*(line + 1)))
		return (parse_check_amb(line, ps));
	else if (*line == 67 && ft_isspace(*(line + 1)))
		return (parse_check_cam(line, ps));
	else if (*line == 76 && ft_isspace(*(line + 1)))
		return (parse_check_light(line, ps));
	return (false);
}

/**
 * @brief Checks current (and next) character for match with scene object. 
 * @param [in] *line: the current line of the scene file. 
 * @param [in] ps: t_parse. 
 * @return True if good, false otherwise.  
 */
bool	char_scene_object(char *line, t_parse ps)
{
	if (*line == 115 && *(line + 1) == 112 && ft_isspace(*(line + 2)))
		return (parse_check_sphere(line, ps));
	else if (*line == 112 && *(line + 1) == 108 && ft_isspace(*(line + 2)))
		return (parse_check_plane(line, ps));
	else if (*line == 99 && *(line + 1) == 121 && ft_isspace(*(line + 2)))
		return (parse_check_cyl(line, ps));
	return (false);
}
