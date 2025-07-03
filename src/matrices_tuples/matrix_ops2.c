/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:08:40 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/03 19:08:41 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4	multiply_mtrx_by_mtrx(t_matrix4 m, t_matrix4 m2)
{
	size_t		i;
	size_t		j;
	size_t		k;
	t_matrix4	m3;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m3.m[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				m3.m[i][j] += m.m[i][k] * m2.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (m3);
}

static void	init_input_output(float input[4], float output[4], t_tuple t1)
{
	size_t	i;

	input[0] = t1.x;
	input[1] = t1.y;
	input[2] = t1.z;
	input[3] = t1.w;
	i = 0;
	while (i < 4)
		output[i++] = 0;
}

t_tuple	multiply_mtrx_by_tuple(t_matrix4 m, t_tuple t1)
{
	t_tuple	new_tuple;
	float	input[4];
	float	output[4];
	size_t	i;
	size_t	j;

	init_input_output(input, output, t1);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			output[i] += m.m[i][j] * input[j];
			j++;
		}
		i++;
	}
	new_tuple.x = output[0];
	new_tuple.y = output[1];
	new_tuple.z = output[2];
	new_tuple.w = output[3];
	return (new_tuple);
}
