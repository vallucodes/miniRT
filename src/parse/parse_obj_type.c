#include "../../inc/minirt.h"

/**
 * @brief Checks current character for match with optical object (light, camera....). 
 */
bool	char_optical_object(char *line, t_parse ps)
{
	if (*line == 65)
		return (parse_check_amb(line, ps));
	else if (*line == 67)
		return (parse_check_cam(line, ps));
	else if (*line == 76)
		return (parse_check_light(line, ps));
	return (false);
}

/**
 * @brief Checks current (and next) character for match with scene object (sphere, plane....). 
 */
bool	char_scene_object(char *line, t_parse ps)
{
	if (*line == 115 && *(line+1) == 112)
		return (parse_check_sphere(line, ps));
	else if (*line == 112 && *(line+1) == 108)
		return (parse_check_plane(line, ps));
	else if (*line == 99 && *(line+1) == 121)
		return (parse_check_cyl(line, ps));
    return (false);
}
