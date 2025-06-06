#include "../../inc/minirt.h"

/**
 * @brief Checks current line is valid A (ambient) line. 
 * @param [in] *line: current line of scene file. 
 * @param [in] ps: t_parse
 * @return True if the line is a proper A line
 * @note Pattern is: A  [0.0,1.0]  [0,255],[0,255],[0,255]
 * @details Allocates memory to **words via line_split_set(). 
 */
bool	parse_check_amb(char *line, t_parse *ps)
{
	char	**words;

	words = line_split_set(line, " \t");
	if (fun_words(line, " \t") != 3)
		return (free_helper(ps, words, NULL, ERR_AMB));
	if (!parse_check_ratio(words[1], &ps->amb_s.ratio))
		return (free_helper(ps, words, NULL, ERR_AMB));
	if (!parse_check_rgb(words[2], &ps->amb_s.r, &ps->amb_s.g, &ps->amb_s.b))
		return (free_helper(ps, words, NULL, ERR_AMB));
	ps->amb_b++;
	parse_fill_colour(&ps->amb_s.col, ps->amb_s.r, ps->amb_s.g, ps->amb_s.b);
	free_matrix(words);
	return (true);
}

/**
 * @brief Checks current line is a valid C (camera) line. 
 * @param [in] *line: current line of scene file. 
 * @param [in] ps: t_parse
 * @return True if the line is a proper C line
 * @note Pattern is: C [x],[y],[z] [-1.0,1.0],[-1.0,1.0],[-1.0,1.0] [0,180]
 * @details Allocates memory to **w via line_split_set(). 
 */
bool	parse_check_cam(char *line, t_parse *ps)
{
	char	**w;

	w = line_split_set(line, " \t");
	if (fun_words(line, " \t") != 4)
		return (free_helper(ps, w, NULL, ERR_CAM));
	if (!parse_check_coords(w[1], &ps->cam_s.cx, &ps->cam_s.cy, &ps->cam_s.cz))
		return (free_helper(ps, w, NULL, ERR_CAM));
	if (!parse_check_orient(w[2], &ps->cam_s.ox, &ps->cam_s.oy, &ps->cam_s.oz))
		return (free_helper(ps, w, NULL, ERR_CAM));
	if (!parse_check_fov(w[3], &ps->cam_s.fov))
		return (free_helper(ps, w, NULL, ERR_CAM));
	ps->cam_b++;
	parse_fill_origin(&ps->cam_s.ori, ps->cam_s.cx, ps->cam_s.cy, ps->cam_s.cz);
	parse_fill_norm(&ps->cam_s.nor, ps->cam_s.ox, ps->cam_s.oy, ps->cam_s.oz);
	free_matrix(w);
	return (true);
}

/**
 * @brief Checks current line is a valid L (light) line. 
 * @param [in] *line: current line of scene file
 * @param [in] ps: t_parse
 * @return True if the line is a proper L line
 * @note Pattern is: L	[x],[y],[z]	[0.0,1.0] - RGB only for bonus. 
 * @details Allocates memory to **w via line_split_set(). 
 */
bool	parse_check_light(char *line, t_parse *ps)
{
	char	**w;

	w = line_split_set(line, " \t");
	if (fun_words(line, " \t") != 3)
		return (free_helper(ps, w, NULL, ERR_DIFF));
	if (!parse_check_coords(w[1], &ps->lig_s.cx, &ps->lig_s.cy, &ps->lig_s.cz))
		return (free_helper(ps, w, NULL, ERR_DIFF));
	if (!parse_check_ratio(w[2], &ps->lig_s.ratio))
		return (free_helper(ps, w, NULL, ERR_DIFF));
	ps->lig_b++;
	parse_fill_origin(&ps->lig_s.ori, ps->lig_s.cx, ps->lig_s.cy, ps->lig_s.cz);
	free_matrix(w);
	return (true);
}
