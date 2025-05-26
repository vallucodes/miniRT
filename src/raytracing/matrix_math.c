#include "minirt.h"

float	**matrix_alloc(t_minirt *minirt, size_t size)
{
	size_t	i;
	float	**m;

	i = 0;
	m = arena_alloc(minirt->arena, size * sizeof(float *), alignof(float *));
	// if (!m)
		// cleanup_exit(arena);
	while (i < size)
	{
		m[i] = arena_alloc(minirt->arena, size * sizeof(float), alignof(float));
		// if (!m[i])
			// cleanup_exit(arena);
		i++;
	}
	return (m);
}

bool	equality_matrix(float **m, float **m2, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (!is_equal(m[i][j], m2[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

float	**multiply_mtrx_by_mtrx(t_minirt *minirt, float **m, float **m2, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	float	**m3;

	m3 = matrix_alloc(minirt, size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			m3[i][j] = 0;
			k = 0;
			while (k < size)
			{
				m3[i][j] += m[i][k] * m2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (m3);
}

void	init_input_output(float input[4], float output[4], t_tuple t1, size_t size)
{
	size_t	i;

	input[0] = t1.x;
	input[1] = t1.y;
	input[2] = t1.z;
	input[3] = t1.w;
	i = 0;
	while (i < size)
		output[i++] = 0;
}

t_tuple	multiply_mtrx_by_tuple(float **m, t_tuple t1, size_t size)
{
	t_tuple	new_tuple;
	float	input[4];
	float	output[4];
	size_t	i;
	size_t	j;

	init_input_output(input, output, t1, size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			output[i] += m[i][j] * input[j];
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

float	**transpose_matrix(t_minirt *minirt, float **m, size_t size)
{
	size_t	i;
	size_t	j;
	float	**m2;

	m2 = matrix_alloc(minirt, size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			m2[i][j] = m[j][i];
			j++;
		}
		i++;
	}
	return (m2);
}

float	**sub_matrix(t_matrix_ctx *ctx, size_t row, size_t col)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	float	**m2;

	m2 = matrix_alloc(ctx->minirt, ctx->size);
	i = 0;
	k = 0;
	while (i < ctx->size)
	{
		if (i == row)
		{
			i++;
			continue ;
		}
		j = 0;
		l = 0;
		while (j < ctx->size)
		{
			if (j == col)
			{
				j++;
				continue ;
			}
			m2[k][l] = ctx->m[i][j];
			j++;
			l++;
		}
		i++;
		k++;
	}
	return (m2);
}

float	minor_matrix(t_matrix_ctx *ctx, int row, int col)
{
	float	**m2;

	m2 = sub_matrix(ctx, row, col);
	return (determinant_matrix(ctx->minirt, m2, ctx->size - 1));
}

float	cofactor_matrix(t_matrix_ctx *ctx, int row, int col)
{
	float	minor;

	minor = minor_matrix(ctx, row, col);
	if ((row + col) % 2 == 1)
		return (-minor);
	return (minor);
}

float	determinant_matrix(t_minirt *minirt, float **m, size_t size)
{
	float	det;
	size_t	j;
	t_matrix_ctx	ctx;

	ctx.minirt = minirt;
	ctx.m = m;
	ctx.size = size;
	det = 0;
	if (size == 2)
		det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	else
	{
		j = 0;
		while (j < size)
		{
			det += m[0][j] * cofactor_matrix(&ctx, 0, j);
			j++;
		}
	}
	return (det);
}

bool	is_invertible_matrix(t_minirt *minirt, float **m, size_t size)
{
	return (determinant_matrix(minirt, m, size) != 0);
}

float	**inverse_matrix(t_minirt *minirt, float **m, size_t size)
{
	float			det;
	size_t			i;
	size_t			j;
	float			**m2;
	t_matrix_ctx	ctx;

	ctx.minirt = minirt;
	ctx.m = m;
	ctx.size = size;
	det = determinant_matrix(minirt, m, size);
	if (det == 0)
		return (NULL);
	m2 = matrix_alloc(minirt, size);
	i = 0;
	if (size == 2)
	{
		m2[0][0] = m[1][1] / det;
		m2[0][1] = -m[0][1] / det;
		m2[1][0] = -m[1][0] / det;
		m2[1][1] = m[0][0] / det;
	}
	else
	{
		while (i < size)
		{
			j = 0;
			while (j < size)
			{
				m2[j][i] = cofactor_matrix(&ctx, i, j) / det;
				j++;
			}
			i++;
		}
	}
	return(m2);
}
