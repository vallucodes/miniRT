#include "minirt.h"

bool	equality_matrix(float m1[4][4], float m2[4][4], size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (!is_equal(m1[i][j], m2[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

float	**multiply_mtrx_by_mtrx(float m1[4][4], float m2[4][4], size_t size)
{
	size_t	i;
	size_t	j;
	float	**m3;

	i = 0;
	m3 = (float **)malloc(sizeof(float) * size * size);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			m3[i][j] = m1[i][0] * m2[0][j] +
						m1[i][1] * m2[1][j] +
						m1[i][2] * m2[2][j] +
						m1[i][3] * m2[3][j];
			j++;
		}
		i++;
	}
	return (m3);
}

float	**multiply_mtrx_by_tuple(float m1[4][4], t_tuple t1, size_t size)
{
	t_tuple	new_tuple;

	new_tuple.x = m1[i][0] * t1.x +
				m1[i][1] * t1.y +
				m1[i][2] * t1.z +
				m1[i][3] * t1.w;
	new_tuple.y = m1[i][0] * t1.x +
				m1[i][1] * t1.y +
				m1[i][2] * t1.z +
				m1[i][3] * t1.w;
	new_tuple.z = m1[i][0] * t1.x +
				m1[i][1] * t1.y +
				m1[i][2] * t1.z +
				m1[i][3] * t1.w;
	new_tuple.w = m1[i][0] * t1.x +
				m1[i][1] * t1.y +
				m1[i][2] * t1.z +
				m1[i][3] * t1.w;
	return (new_tuple);
}

float	**transpose_matrix(float m1[4][4], size_t size)
{
	size_t	i;
	size_t	j;
	float	**m2;

	i = 0;
	m2 = (float **)malloc(sizeof(float) * size * size);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			m2[i][j] = m1[j][i];
			j++;
		}
		i++;
	}
	return (m2);
}

float	**sub_matrix(float m1[4][4], int row, int col, size_t size)
{
	size_t	i;
	size_t	j;
	float	**m2;

	i = 0;
	m2 = (float **)malloc(sizeof(float) * (size - 1) * (size - 1));
	while (i < size)
	{
		if (size == row)
		{
			i++;
			continue ;
		}
		j = 0;
		while (j < size)
		{
			if (size == col)
			{
				j++;
				continue ;
			}
			m2[i][j] = m1[j][i];
			j++;
		}
		i++;
	}
	return (m2);
}

int	minor_matrix(float m1[3][3], int row, int col, size_t size)
{
	float	**m2;

	m2 = (float **)malloc(sizeof(float) * (size - 1) * (size - 1));
	m2 = sub_matrix(m1, row, col);
	return (determinant_matrix(m2));
}

int	cofactor_matrix(float m1[3][3], int row, int col, size_t size)
{
	int	minor;

	minor = minor_matrix(m1, row, col, size);
	if ((row + col) % 2 == 1)
		return (-minor);
	return (minor);
}

int	determinant_matrix(float m1[3][3], size_t size) //very uncertain about this
{
	if (size == 2)
		det = m1[0][0] * m1[1][1] - m1[0][1] * m1[1][0];
	else
	{
		while (col < size - 1)
		{
			det = det + m1[0][col] * cofactor_matrix(m1, 0, col)
			col++;
		}
	}
	return (det);
}

bool	is_invertible_matrix(float m1[4][4], size_t size)
{
	return (determinant(m1, size) != 0);
}

float	**inverse_matrix(float m1[4][4], size_t size)
{
	float	**m2;
	int		row;
	int		col;

	if (!is_invertible_matrix(m1, size))
		return (NULL);
	m2 = (float **)malloc(sizeof(float) * (size - 1) * (size - 1));
	row = 0;
	col = 0;
	else
	{
		while (row < size - 1)
		{
			while (col < size - 1)
			{
				c = cofactor_matrix(m1, row, col, size);
				m2[col, row] = c / determinant_matrix(m1);
			}
		}
	}
	return (m2);
}
