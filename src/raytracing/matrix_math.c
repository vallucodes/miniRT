#include "minirt.h"

// float	**matrix_alloc(t_minirt *minirt, size_t size)
// {
// 	size_t	i;
// 	float	**m;

// 	i = 0;
// 	m = arena_alloc(minirt->arena, size * sizeof(float *), alignof(float *));
// 	// if (!m)
// 		// cleanup_exit(arena);
// 	while (i < size)
// 	{
// 		m[i] = arena_alloc(minirt->arena, size * sizeof(float), alignof(float));
// 		// if (!m[i])
// 			// cleanup_exit(arena);
// 		i++;
// 	}
// 	return (m);
// }

bool	equality_matrix4(t_matrix4 m, t_matrix4 m2, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (!is_equal(m.m[i][j], m2.m[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

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

t_matrix_result sub_matrix(t_matrix_ctx *ctx, size_t row, size_t col)
{
	size_t i, j, k, l;
	t_matrix_result result;
	size_t new_size = ctx->size - 1;

	result.size = new_size;
	i = 0;
	k = 0;

	while (i < ctx->size && k < new_size)
	{
		if (i == row)
		{
			i++;
			continue;
		}
		j = 0;
		l = 0;
		while (j < ctx->size && l < new_size)
		{
			if (j == col)
			{
				j++;
				continue;
			}
			if (new_size == 2)
				result.m.m2.m[k][l] = ctx->m.m[i][j];
			else if (new_size == 3)
				result.m.m3.m[k][l] = ctx->m.m[i][j];

			j++;
			l++;
		}
		i++;
		k++;
	}
	return (result);
}

float	minor_matrix(t_matrix_ctx *ctx, int row, int col)
{
	t_matrix_result sub = sub_matrix(ctx, row, col);

	if (sub.size == 2)
		return determinant_matrix2(sub.m.m2);
	else if (sub.size == 3)
		return determinant_matrix3(sub.m.m3);
	return (0);
}

float	cofactor_matrix(t_matrix_ctx *ctx, int row, int col)
{
	float minor;

	minor = minor_matrix(ctx, row, col);
	if ((row + col) % 2 == 1)
		return (-minor);
	return (minor);
}

float	determinant_matrix2(t_matrix2 m)
{
	return m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
}

float	determinant_matrix3(t_matrix3 m)
{
	float			det;
	size_t			j;
	t_matrix_ctx	ctx;

	ctx.m.m[0][0] = m.m[0][0];
	ctx.m.m[0][1] = m.m[0][1];
	ctx.m.m[0][2] = m.m[0][2];
	ctx.m.m[1][0] = m.m[1][0];
	ctx.m.m[1][1] = m.m[1][1];
	ctx.m.m[1][2] = m.m[1][2];
	ctx.m.m[2][0] = m.m[2][0];
	ctx.m.m[2][1] = m.m[2][1];
	ctx.m.m[2][2] = m.m[2][2];
	ctx.size = 3;
	det = 0;
	j = 0;
	while (j < 3)
	{
		det += m.m[0][j] * cofactor_matrix(&ctx, 0, j);
		j++;
	}
	return (det);
}

float	determinant_matrix4(t_matrix4 m)
{
	float det;
	size_t j;
	t_matrix_ctx ctx;

	ctx.m = m;
	ctx.size = 4;
	det = 0;
	j = 0;
	while (j < 4)
	{
		det += m.m[0][j] * cofactor_matrix(&ctx, 0, j);
		j++;
	}
	return det;
}

bool	is_invertible_matrix2(t_matrix2 m)
{
	return (determinant_matrix2(m) != 0);
}

bool	is_invertible_matrix3(t_matrix3 m)
{
	return (determinant_matrix3(m) != 0);
}

bool	is_invertible_matrix4(t_matrix4 m)
{
	return (determinant_matrix4(m) != 0);
}

t_matrix4	inverse_matrix(t_matrix4 m, bool *success)
{
	float det;
	size_t i;
	size_t j;
	t_matrix4	m2;
	t_matrix_ctx ctx;

	ctx.m = m;
	ctx.size = 4;
	det = determinant_matrix4(m);
	if (det == 0)
	{
		*success = false;
		return (m2);
	}
	*success = true;
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
	return (m2);
}
