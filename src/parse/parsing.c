#include "../../inc/minirt.h"

/**
 * @brief Launchpad for parsing operations. 
 * @param [in] ps: t_parse type, parsing struct. 
 * @return True on success.
 * @note Allocates memory to *line via get_next_line().  
 */
bool	parsing_gateway(t_parse *ps)
{
	char	*line;
	char	*ph;

	while (line != NULL)
	{
		line = get_next_line(ps->fd);
		if (!line)
			return (false);
		ph = line;
		while (*ph && *ph != '\n' && ft_isspace(*ph))
			ph++;
		if (parse_optical_object(ph, ps))
			;
		else if (parse_scene_object(ph, ps))
			;
		else if (*ph == '\n')
			;
		else
		{
			free(line);
			line = NULL;
			return (false);
		}
		free(line);
	}
	return (true);
}
