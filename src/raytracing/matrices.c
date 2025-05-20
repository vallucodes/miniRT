#include "minirt.h"

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

float	**multiply_mtrx_by_mtrx(float **m, float **m2, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	float	**m3;

	i = 0;
	m3 = malloc(size * sizeof(float *));
	// if (!m3)
		// cleanup_exit(arena);
	while (i < size)
	{
		m3[i] = malloc(size * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
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

float	**transpose_matrix(float **m, size_t size)
{
	size_t	i;
	size_t	j;
	float	**m2;

	i = 0;
	m2 = malloc(size * sizeof(float *));
	while (i < size)
	{
		m2[i] = malloc(size * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
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

float	**sub_matrix(float **m, size_t row, size_t col, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	float	**m2;

	i = 0;
	m2 = malloc((size - 1) * sizeof(float *));
	while (i < (size - 1))
	{
		m2[i] = malloc((size - 1) * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
	i = 0;
	k = 0;
	while (i < size)
	{
		if (i == row)
		{
			i++;
			continue ;
		}
		j = 0;
		l = 0;
		while (j < size)
		{
			if (j == col)
			{
				j++;
				continue ;
			}
			m2[k][l] = m[i][j];
			j++;
			l++;
		}
		i++;
		k++;
	}
	return (m2);
}

float	minor_matrix(float **m, int row, int col, size_t size)
{
	float	**m2;

	m2 = sub_matrix(m, row, col, size);
	return (determinant_matrix(m2, size - 1));
}

float	cofactor_matrix(float **m, int row, int col, size_t size)
{
	int	minor;

	minor = minor_matrix(m, row, col, size);
	if ((row + col) % 2 == 1)
		return (-minor);
	return (minor);
}

float	determinant_matrix(float **m, size_t size)
{
	int		det;
	size_t	j;

	det = 0;
	if (size == 2)
		det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	else
	{
		j = 0;
		while (j < size)
		{
			det += m[0][j] * cofactor_matrix(m, 0, j, size);
			j++;
		}
	}
	return (det);
}

bool	is_invertible_matrix(float **m, size_t size)
{
	return (determinant_matrix(m, size) != 0);
}

float	**inverse_matrix(float **m, size_t size)
{
	float	det;
	size_t	i;
	size_t	j;
	float	**m2;

	det = determinant_matrix(m, size);
	if (det == 0)
		return (NULL);
	m2 = malloc(size * sizeof(float *));
	i = 0;
	while (i < size)
	{
		m2[i] = malloc(size * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			m2[j][i] = cofactor_matrix(m, i, j, size) / det;
			j++;
		}
		i++;
	}
	return(m2);
}
