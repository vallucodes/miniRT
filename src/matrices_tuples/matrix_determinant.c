#include "minirt.h"

float	cofactor_matrix(t_matrix_ctx *ctx, int row, int col)
{
	float	minor;

	minor = minor_matrix(ctx, row, col);
	if ((row + col) % 2 == 1)
		return (-minor);
	return (minor);
}

float	determinant_matrix2(t_matrix2 m)
{
	return (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]);
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
	size_t			i;
	float			det;
	t_matrix_ctx	ctx;

	ctx.m = m;
	ctx.size = 4;
	det = 0;
	i = 0;
	while (i < 4)
	{
		det += m.m[0][i] * cofactor_matrix(&ctx, 0, i);
		i++;
	}
	return (det);
}
