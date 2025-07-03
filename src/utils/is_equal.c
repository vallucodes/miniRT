/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_equal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:08:04 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/03 19:08:05 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline bool	is_equal(float a, float b)
{
	float	res;

	res = fabs(a - b);
	if (res < EPSILON)
		return (true);
	return (false);
}
