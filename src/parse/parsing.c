#include "../../inc/minirt.h"

/**
 * @brief Launchpad for parsing operations. 
 * @param [in] ps: t_parse type, parsing struct. 
 * @return false on fail, true on success. 
 */
bool	parsing_gateway(t_parse ps)
{
	char	*line;

	line = "";
	while (line != NULL)
	{
		line = get_next_line(ps.fd);
		if (char_optical_object(line, ps))
			;
		else if (char_scene_object(line, ps))
			;
		else
		{
			free(line);
			return (false);
		}
		free(line);
	}
}
