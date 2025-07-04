/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:55:40 by elehtone          #+#    #+#             */
/*   Updated: 2025/07/04 14:41:37 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Helper for parsing_gateway(). 
 */
static bool	parse_choose_type(char *ph, t_parse *ps)
{
	if (*ph == '\n')
		return (true);
	else if (*ph && ft_isalnum(*ph) && ft_isspace(*(ph + 1)))
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
 * @todo get_next_line() leak
 */
bool	parsing_gateway(t_parse *ps)
{
	char	*line;
	char	*ph;

	line = "";
	while (line != NULL)
	{
		line = get_next_line(ps->fd, false);
		if (!line)
			return (false);
		if (*line == '\0')
		{
			(void)get_next_line(ps->fd, true);
			break ;
		}
		ph = line;
		while (*ph && *ph != '\n' && ft_isspace(*ph))
			ph++;
		if (!parse_choose_type(ph, ps))
			free_helper(ps, NULL, NULL, ERR_GEN);
		free(line);
	}
	free(line);
	if (ps->obj_count > OBJ_MAX)
		return (free_helper(ps, NULL, NULL, ERR_NUM_OBJ));
	return (true);
}
