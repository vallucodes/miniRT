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

	line = "";
	while (line != NULL)
	{
		line = get_next_line(ps->fd);
		if (!line)
			return (false);
		if (parse_optical_object(line, ps))
			;
		else if (parse_scene_object(line, ps))
			;
		else
		{
			free_void(line);
			return (false);
		}
		free_void(line);
	}
	return (true);
}
