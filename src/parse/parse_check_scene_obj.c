#include "../../inc/minirt.h"

/**
 * @brief Checks current line is a valid pl (plane) line.
 * @param [in] *line: current line of scene file.
 * @param [in] ps: t_parse
 * @return True if the line is a proper pl line
 * @note Pattern is: pl [x],[y],[z] [-1,1],[-1,1],[-1,1] [0,255],[0,255],[0,255]
 * @details - allocates memory to *tmp via ft_calloc()
 * 			- allocates memory to **words via line_split_set()
 */
bool	parse_check_plane(char *line, t_parse *ps)
{
	t_scene_obj	*tmp;
	char		**words;

	tmp = ft_calloc(1, sizeof(t_scene_obj));
	words = line_split_set(line, " \t");
	if (!tmp || !words)
		return (free_helper(ps, words, tmp, ERR_ALLOC));
	if (fun_words(line, " \t") != 4)
		return (free_helper(ps, words, tmp, ERR_PLANE));
	if (!parse_check_coords(words[1], &tmp->cx, &tmp->cy, &tmp->cz))
		return (free_helper(ps, words, tmp, ERR_PLANE));
	if (!parse_check_orient(words[2], &tmp->ox, &tmp->oy, &tmp->oz))
		return (free_helper(ps, words, tmp, ERR_PLANE));
	if (!parse_check_rgb(words[3], &tmp->r, &tmp->g, &tmp->b))
		return (free_helper(ps, words, tmp, ERR_PLANE));
	tmp->type = 0;
	ps->obj_count++;
	parse_fill_origin(&tmp->ori, tmp->cx, tmp->cy, tmp->cz);
	parse_fill_norm(&tmp->nor, tmp->ox, tmp->oy, tmp->oz);
	parse_fill_colour(&tmp->col, tmp->r, tmp->g, tmp->b);
	free_matrix(words);
	return (parse_add_obj_list(tmp, ps));
}

/**
 * @brief Checks current line is a valid sp (sphere) line.
 * @param [in] *line: current line of scene file.
 * @param [in] ps: t_parse
 * @return True if the line is a proper sp line
 * @note Pattern is: sp	 [x],[y],[z]	[0.0,?]	[0,255],[0,255],[0,255]
 * @details - allocates memory to *tmp via ft_calloc()
 * 			- allocates memory to **words via line_split_set()
 */
bool	parse_check_sphere(char *line, t_parse *ps)
{
	t_scene_obj	*tmp;
	char		**words;

	tmp = ft_calloc(1, sizeof(t_scene_obj));
	words = line_split_set(line, " \t");
	if (!tmp || !words)
		return (free_helper(ps, words, tmp, ERR_ALLOC));
	if (fun_words(line, " \t") != 4)
		return (free_helper(ps, words, tmp, ERR_PLANE));
	if (!parse_check_coords(words[1], &tmp->cx, &tmp->cy, &tmp->cz))
		return (free_helper(ps, words, tmp, ERR_SPHERE));
	if (!parse_check_geometry(words[2], &tmp->dia))
		return (free_helper(ps, words, tmp, ERR_SPHERE));
	if (!parse_check_rgb(words[3], &tmp->r, &tmp->g, &tmp->b))
		return (free_helper(ps, words, tmp, ERR_SPHERE));
	tmp->type = 1;
	ps->obj_count++;
	parse_fill_origin(&tmp->ori, tmp->cx, tmp->cy, tmp->cz);
	parse_fill_norm(&tmp->nor, tmp->ox, tmp->oy, tmp->oz);
	parse_fill_colour(&tmp->col, tmp->r, tmp->g, tmp->b);
	free_matrix(words);
	return (parse_add_obj_list(tmp, ps));
}

void	parse_dumb(t_obj_type *type, t_parse *ps)
{
	*type = 2;
	ps->obj_count++;
}

/**
 * @brief Checks current line is a valid cy (cylinder) line.
 * @param [in] *line: current line of scene file.
 * @param [in] ps: t_parse
 * @return True if the line is a proper cy line
 * @note Pat: cy [x],[y],[z] [-1,1],[-1,1],[-1,1] [0.0,?] [0.0,?] [r],[g],[b]
 * @details - allocates memory to *tmp via ft_calloc()
 * 			- allocates memory to **words via line_split_set()
 */
bool	parse_check_cylinder(char *line, t_parse *ps)
{
	t_scene_obj	*tmp;
	char		**words;

	tmp = ft_calloc(1, sizeof(t_scene_obj));
	words = line_split_set(line, " \t");
	if (!tmp || !words)
		return (free_helper(ps, words, tmp, ERR_ALLOC));
	if (fun_words(line, " \t") != 6)
		return (free_helper(ps, words, tmp, ERR_PLANE));
	if (!parse_check_coords(words[1], &tmp->cx, &tmp->cy, &tmp->cz))
		return (free_helper(ps, words, tmp, ERR_CYL));
	if (!parse_check_orient(words[2], &tmp->ox, &tmp->oy, &tmp->oz))
		return (free_helper(ps, words, tmp, ERR_CYL));
	if (!parse_check_geometry(words[3], &tmp->dia))
		return (free_helper(ps, words, tmp, ERR_CYL));
	if (!parse_check_geometry(words[4], &tmp->height))
		return (free_helper(ps, words, tmp, ERR_CYL));
	if (!parse_check_rgb(words[5], &tmp->r, &tmp->g, &tmp->b))
		return (free_helper(ps, words, tmp, ERR_CYL));
	parse_dumb(&tmp->type, ps);
	parse_fill_origin(&tmp->ori, tmp->cx, tmp->cy, tmp->cz);
	parse_fill_norm(&tmp->nor, tmp->ox, tmp->oy, tmp->oz);
	parse_fill_colour(&tmp->col, tmp->r, tmp->g, tmp->b);
	free_matrix(words);
	return (parse_add_obj_list(tmp, ps));
}
