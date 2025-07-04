/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:55:31 by elehtone          #+#    #+#             */
/*   Updated: 2025/07/03 21:56:10 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Checks first character for match with optical object.
 * @param [in] *line: current line of scene file.
 * @param [in] ps: t_parse
 * @return True on successful parse
 */
bool	parse_optical_object(char *line, t_parse *ps)
{
	if (*line && *line == 65 && ft_isspace(*(line + 1)))
		return (parse_check_amb(line, ps));
	else if (*line == 67 && ft_isspace(*(line + 1)))
		return (parse_check_cam(line, ps));
	else if (*line == 76 && ft_isspace(*(line + 1)))
		return (parse_check_light(line, ps));
	else
		free_helper(ps, NULL, NULL, ERR_OPTICAL);
	return (false);
}

/**
 * @brief Checks first and second characters for match with scene object.
 * @param [in] *line: current line of scene file.
 * @param [in] ps: t_parse
 * @return True on successful parse
 */
bool	parse_scene_object(char *line, t_parse *ps)
{
	if (*line == 115 && *(line + 1) == 112 && ft_isspace(*(line + 2)))
		return (parse_check_sphere(line, ps));
	else if (*line == 112 && *(line + 1) == 108 && ft_isspace(*(line + 2)))
		return (parse_check_plane(line, ps));
	else if (*line == 99 && *(line + 1) == 121 && ft_isspace(*(line + 2)))
		return (parse_check_cylinder(line, ps));
	else
		free_helper(ps, NULL, NULL, ERR_SCENE);
	return (false);
}
