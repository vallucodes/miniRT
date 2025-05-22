#include "../../inc/minirt.h"

/**
 * @brief Launchpad for parsing operations. 
 * @param [in] ps: t_parse
 * @return True on successful parse 
 * @details Allocates memory to *line via get_next_line(). 
 * 
 * Not worried about lines at the moment. This function will probably change a lot.
 * If it even exists in this form when we are done. 
 * Also, my GNL is the leaky kind. Will fix that in future or swap for Vallu's
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
		else if (*ph && ft_isalnum(*ph) && ft_isspace(*(ph + 1)))
		{
			if (!parse_optical_object(ph, ps))
			{
				free(line);
				return (false);
			}
		}
		else if (*ph && ft_isalnum(*ph) && ft_isalnum(*(ph + 1))
			&& ft_isspace(*(ph + 2)))
		{
			if (!parse_scene_object(ph, ps))
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
	return (true);
}
