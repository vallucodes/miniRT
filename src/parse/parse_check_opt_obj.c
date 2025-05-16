#include "../../inc/minirt.h"

/**
 * @brief Checks the current line is a valid A (ambient) line. 
 * @param [in] *line: the current line of the scene file. 
 * @param [in] ps: t_parse, parsing struct. 
 * @return True if the line is a proper A line, false otherwise. 
 * @note Pattern is: A  [0.0,1.0]  [0,255],[0,255],[0,255]
 * - allocates memory to **words via line_split_set(). 
 */
bool	parse_check_amb(char *line, t_parse ps)
{
	char	**words;

	words = line_split_set(line, " \t");
	if (!parse_check_ratio(words[1], &ps.amb_s.ratio))
		return (false);
	if (!parse_check_rgb(words[2], &ps.amb_s.r, &ps.amb_s.g, &ps.amb_s.b))
		return (false);
	ps.amb_b = true;
	return (true);
}

/**
 * @brief Checks the current line is a valid C (camera) line. 
 * @param [in] *line: the current line of the scene file. 
 * @param [in] ps: t_parse, parsing struct. 
 * @return True if the line is a proper C line, false otherwise. 
 * @note Pattern is: C [x],[y],[z] [-1.0,1.0],[-1.0,1.0],[-1.0,1.0] [0,180]
 * - allocates memory to **words via line_split_set(). 
 */
bool	parse_check_cam(char *line, t_parse ps)
{
	char	**words;

	words = line_split_set(line, " \t");
	if (!parse_check_coords(words[1], &ps.cam_s.cx, &ps.cam_s.cy, &ps.cam_s.cz))
		return (false);
	if (!parse_check_orient(words[2], &ps.cam_s.ox, &ps.cam_s.oy, &ps.cam_s.oz))
		return (false);
	if (!parse_check_fov(words[3], &ps.cam_s.fov))
		return (false);
	ps.cam_b++;
	return (true);
}

/**
 * @brief Checks the current line is a valid L (light) line. 
 * @param [in] *line: current line. 
 * @param [in] ps: t_parse type. 
 * @return True if the line is a proper L line, false otherwise. 
 * @note Pattern is: L	[x],[y],[z]	[0.0,1.0] - RGB only for bonus. 
 * - allocates memory to **words via line_split_set(). 
 */
bool	parse_check_light(char *line, t_parse ps)
{
	char	**words;

	words = line_split_set(line, " \t");
	if (!parse_check_coords(words[1], &ps.lig_s.cx, &ps.lig_s.cy, &ps.lig_s.cz))
		return (false);
	if (!parse_check_ratio(words[2], &ps.lig_s.ratio))
		return (false);
	ps.lig_b++;
	return (true);
}
