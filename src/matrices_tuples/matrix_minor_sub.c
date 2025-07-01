#include "minirt.h"

static t_matrix_result	init_submatrix_result(size_t original_size)
{
	t_matrix_result	result;

	result.size = original_size - 1;
	return (result);
}

static void	copy_matrix_row(t_matrix_ctx *ctx, t_matrix_result *result, t_row_copy_params params)
{
	size_t	j;
	size_t	l;

	j = 0;
	l = 0;
	while (j < ctx->size && l < result->size)
	{
		if (j == params.skip_col)
		{
			j++;
			continue;
		}
		if (result->size == 2)
		{
			printf("yes\n");
			result->m.m2.m[params.dest_row][l] = ctx->m.m[params.src_row][j];
		}
		else if (result->size == 3)
			result->m.m3.m[params.dest_row][l] = ctx->m.m[params.src_row][j];
		j++;
		l++;
	}
}

static void	copy_matrix_rows(t_matrix_ctx *ctx, t_matrix_result *result, size_t skip_row, size_t skip_col)
{
	t_row_copy_params	params;
	size_t				i;
	size_t				k;

	i = 0;
	k = 0;
	params.skip_col = skip_col;
	while (i < ctx->size && k < result->size)
	{
		if (i == skip_row)
		{
			i++;
			continue;
		}
		params.src_row = i;
		params.dest_row = k;
		copy_matrix_row(ctx, result, params);
		i++;
		k++;
	}
}

t_matrix_result	sub_matrix(t_matrix_ctx *ctx, size_t row, size_t col)
{
	t_matrix_result	result;

	result = init_submatrix_result(ctx->size);
	copy_matrix_rows(ctx, &result, row, col);
	return (result);
}

float	minor_matrix(t_matrix_ctx *ctx, int row, int col)
{
	t_matrix_result	sub;

	sub = sub_matrix(ctx, row, col);
	if (sub.size == 2)
		return (determinant_matrix2(sub.m.m2));
	else if (sub.size == 3)
		return (determinant_matrix3(sub.m.m3));
	return (0);
}
