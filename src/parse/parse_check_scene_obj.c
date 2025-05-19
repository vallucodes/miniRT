#include "../../inc/minirt.h"

/**
 * @brief Checks the current line is a valid pl (plane) line. 
 * @param [in] *line: the current line of the scene file. 
 * @param [in] ps: t_parse, parsing struct. 
 * @return True if the line is a proper pl line, false otherwise. 
 * @note Pattern is: pl [x],[y],[z] [-1,1],[-1,1],[-1,1] [0,255],[0,255],[0,255]
 * - allocates memory to *tmp via ft_calloc()
 * - allocates memory to **words via line_split_set()
 */
bool	parse_check_plane(char *line, t_parse *ps)
{
	t_scene_obj	*tmp;
	char	**words;

	tmp = ft_calloc(1, sizeof(t_scene_obj));
	words = line_split_set(line, " \t");
	if (!parse_check_coords(words[1], &tmp->cx, &tmp->cy, &tmp->cz))
		return (false);
	if (!parse_check_orient(words[2], &tmp->ox, &tmp->oy, &tmp->oz))
		return (false);
	if (!parse_check_rgb(words[3], &tmp->r, &tmp->g, &tmp->b))
		return (false);
	tmp->type = 0;
	parse_add_obj_list(tmp, ps);
	return (true);
}

/**
 * @brief Checks the current line is a valid sp (sphere) line. 
 * @param [in] *line: the current line of the scene file. 
 * @param [in] ps: t_parse, parsing struct. 
 * @return True if the line is a proper sp line, false otherwise. 
 * @note Pattern is: sp	 [x],[y],[z]	[0.0,?]	[0,255],[0,255],[0,255]
 * - allocates memory to *tmp via ft_calloc()
 * - allocates memory to **words via line_split_set()
 */
bool	parse_check_sphere(char *line, t_parse *ps)
{
	t_scene_obj	*tmp;
	char		**words;

	tmp = ft_calloc(1, sizeof(t_scene_obj));
	words = line_split_set(line, " \t");
	if (!parse_check_coords(words[1], &tmp->cx, &tmp->cy, &tmp->cz))
		return (false);
	if (!parse_check_geometry(words[2], &tmp->dia))
		return (false);
	if (!parse_check_rgb(words[3], &tmp->r, &tmp->g, &tmp->b))
		return (false);
	tmp->type = 1;
	parse_add_obj_list(tmp, ps);
	return (true);
}

/**
 * @brief Checks the current line is a valid cy (cylinder) line. 
 * @param [in] *line: the current line of the scene file. 
 * @param [in] ps: t_parse, parsing struct. 
 * @return True if the line is a proper cy line, false otherwise. 
 * @note Pat: cy [x],[y],[z] [-1,1],[-1,1],[-1,1] [0.0,?] [0.0,?] [r],[g],[b]
 * - allocates memory to *tmp via ft_calloc()
 * - allocates memory to **words via line_split_set()
 */
bool	parse_check_cylinder(char *line, t_parse *ps)
{
	t_scene_obj	*tmp;
	char		**words;

	tmp = ft_calloc(1, sizeof(t_scene_obj));
	words = line_split_set(line, " \t");
	if (!parse_check_coords(words[1], &tmp->cx, &tmp->cy, &tmp->cz))
		return (false);
	if (!parse_check_orient(words[2], &tmp->ox, &tmp->oy, &tmp->oz))
		return (false);
	if (!parse_check_geometry(words[3], &tmp->dia))
		return (false);
	if (!parse_check_geometry(words[4], &tmp->height))
		return (false);
	if (!parse_check_rgb(words[5], &tmp->r, &tmp->g, &tmp->b))
		return (false);
	tmp->type = 2;
	parse_add_obj_list(tmp, ps);
	return (true);
}
