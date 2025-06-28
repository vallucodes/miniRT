#include "../../inc/minirt.h"

/**
 * @brief Helper for parsing_gateway(). Choose between optical or scene function 
 */
static bool	parse_choose_type(char *ph, t_parse *ps)
{
	if (*ph && ft_isalnum(*ph) && ft_isspace(*(ph + 1)))
		return (parse_optical_object(ph, ps));
	else if (*ph && ft_isalnum(*ph) && ft_isalnum(*(ph + 1))
		&& ft_isspace(*(ph + 2)))
		return (parse_scene_object(ph, ps));
	else
		return (false);
}

/**
 * @brief Fills objects in t_parse [ps] from given input .rt file. 
 * @details Allocates memory to *line via get_next_line().
 *
 * @todo Need to trim for norm.
 * @todo My GNL is leaky on exit. Will fix that in future or swap for Vallu's
 */
bool	parsing_gateway(t_parse *ps)
{
	char	*line;
	char	*ph;

	line = "";
	while (line != NULL)
	{
		line = get_next_line(ps->fd);
		if (!line)
			return (false);
		if (*line == '\0')
			break ;
		ph = line;
		while (*ph && *ph != '\n' && ft_isspace(*ph))
			ph++;
		if (*ph == '\n')
			;
		else if (*ph && ft_isalnum(*ph) && (ft_isspace(*(ph + 1))
				|| ft_isalnum(*(ph + 1)) && ft_isspace(*(ph + 2))))
		{
			if (!parse_choose_type(ph, ps))
			{
				free(line);
				return (false);
			}
		}
		else
		{
			free_helper(ps, NULL, line, ERR_GEN);
			return (false);
		}
		free(line);
	}
	free(line);
	if (ps->obj_count > OBJ_MAX)
		return (free_helper(ps, NULL, NULL, ERR_NUM_OBJ));
	return (true);
}
