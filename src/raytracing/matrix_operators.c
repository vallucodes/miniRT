#include "minirt.h"

void	matrix_fill_zero(float **m, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			m[i][j] = 0;
			j++;
		}
		i++;
	}
}

float	**identity(t_minirt *minirt)
{
	float	**m;
	size_t	i;
	size_t	j;
	size_t	size;

	size = 4;
	m = matrix_alloc(minirt, size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
			j++;
		}
		i++;
	}
	return(m);
}

float	**translation(t_minirt *minirt, int x, int y, int z)
{
	float	**m;
	size_t	size;

	size = 4;
	m = matrix_alloc(minirt, size);
	matrix_fill_zero(m, size);
	m[0][0] = 1;
	m[0][3] = x;
	m[1][1] = 1;
	m[1][3] = y;
	m[2][2] = 1;
	m[2][3] = z;
	m[3][3] = 1;
	return(m);
}

float	**scaling(t_minirt *minirt, float x, float y, float z)
{
	float	**m;
	size_t	size;

	size = 4;
	m = matrix_alloc(minirt, size);
	matrix_fill_zero(m, size);
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	m[3][3] = 1;
	return(m);
}

float	**rotation_x(t_minirt *minirt, float theta)
{
	float	**m;
	size_t	size;

	size = 4;
	m = matrix_alloc(minirt, size);
	matrix_fill_zero(m, size);
	m[0][0] = 1;
	m[1][1] = cos(theta);
	m[1][2] = -sin(theta);
	m[2][1] = sin(theta);
	m[2][2] = cos(theta);
	m[3][3] = 1;
	return(m);
}

float	**rotation_y(t_minirt *minirt, float theta)
{
	float	**m;
	size_t	size;

	size = 4;
	m = matrix_alloc(minirt, size);
	matrix_fill_zero(m, size);
	m[0][0] = cos(theta);
	m[0][2] = sin(theta);
	m[1][1] = 1;
	m[2][2] = cos(theta);
	m[2][0] = -sin(theta);
	m[3][3] = 1;
	return(m);
}

float	**rotation_z(t_minirt *minirt, float theta)
{
	float	**m;
	size_t	size;

	size = 4;
	m = matrix_alloc(minirt, size);
	matrix_fill_zero(m, size);
	m[0][0] = cos(theta);
	m[0][1] = -sin(theta);
	m[1][0] = sin(theta);
	m[1][1] = cos(theta);
	m[2][2] = 1;
	m[3][3] = 1;
	return(m);
}
