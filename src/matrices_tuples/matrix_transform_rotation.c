/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transform_rotation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:08:43 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/03 19:08:44 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4	rotation_x(float theta)
{
	t_matrix4	m;

	matrix_fill_zero(&m);
	m.m[0][0] = 1;
	m.m[1][1] = cos(theta);
	m.m[1][2] = -sin(theta);
	m.m[2][1] = sin(theta);
	m.m[2][2] = cos(theta);
	m.m[3][3] = 1;
	return (m);
}

t_matrix4	rotation_y(float theta)
{
	t_matrix4	m;

	matrix_fill_zero(&m);
	m.m[0][0] = cos(theta);
	m.m[0][2] = sin(theta);
	m.m[1][1] = 1;
	m.m[2][2] = cos(theta);
	m.m[2][0] = -sin(theta);
	m.m[3][3] = 1;
	return (m);
}

t_matrix4	rotation_z(float theta)
{
	t_matrix4	m;

	matrix_fill_zero(&m);
	m.m[0][0] = cos(theta);
	m.m[0][1] = -sin(theta);
	m.m[1][0] = sin(theta);
	m.m[1][1] = cos(theta);
	m.m[2][2] = 1;
	m.m[3][3] = 1;
	return (m);
}
