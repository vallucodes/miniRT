/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:08:36 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/03 19:08:37 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4	transpose_matrix(t_matrix4 m)
{
	size_t		i;
	size_t		j;
	t_matrix4	m2;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m2.m[i][j] = m.m[j][i];
			j++;
		}
		i++;
	}
	return (m2);
}

t_matrix4	inverse_matrix(t_matrix4 m, bool *success)
{
	float			det;
	size_t			i;
	size_t			j;
	t_matrix4		m2;
	t_matrix_ctx	ctx;

	ctx.m = m;
	ctx.size = 4;
	matrix_fill_zero(&m2);
	det = determinant_matrix4(m);
	if (det == 0)
		return (*success = false, m2);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m2.m[j][i] = cofactor_matrix(&ctx, i, j) / det;
			j++;
		}
		i++;
	}
	return (*success = true, m2);
}

t_matrix4	scalar_multiply_matrix(t_matrix4 m, float scalar)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[j][i] = m.m[j][i] * scalar;
			j++;
		}
		i++;
	}
	return (m);
}

t_matrix4	addition_matrix(t_matrix4 a, t_matrix4 b)
{
	size_t		i;
	size_t		j;
	t_matrix4	m;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = a.m[i][j] + b.m[i][j];
			j++;
		}
		i++;
	}
	return (m);
}
