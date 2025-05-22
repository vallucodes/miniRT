#include "minirt.h"

float	**identity()
{
	float	**m;
	size_t	i;
	size_t	j;

	m = malloc(4 * sizeof(float *));
	i = 0;
	while (i < 4)
	{
		m[i] = malloc(4 * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
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

float	**translation(int x, int y, int z)
{
	float	**m;
	size_t	i;
	size_t	j;

	m = malloc(4 * sizeof(float *));
	i = 0;
	while (i < 4)
	{
		m[i] = malloc(4 * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m[i][j] = 0;
			j++;
		}
		i++;
	}
	m[0][0] = 1;
	m[0][3] = x;
	m[1][1] = 1;
	m[1][3] = y;
	m[2][2] = 1;
	m[2][3] = z;
	m[3][3] = 1;
	return(m);
}

float	**scaling(int x, int y, int z)
{
	float	**m;
	size_t	i;
	size_t	j;

	m = malloc(4 * sizeof(float *));
	i = 0;
	while (i < 4)
	{
		m[i] = malloc(4 * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m[i][j] = 0;
			j++;
		}
		i++;
	}
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	m[3][3] = 1;
	return(m);
}

float	**rotation_x(float theta)
{
	float	**m;
	size_t	i;
	size_t	j;

	m = malloc(4 * sizeof(float *));
	i = 0;
	while (i < 4)
	{
		m[i] = malloc(4 * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m[i][j] = 0;
			j++;
		}
		i++;
	}
	m[0][0] = 1;
	m[1][1] = cos(theta);
	m[1][2] = -sin(theta);
	m[2][1] = sin(theta);
	m[2][2] = cos(theta);
	m[3][3] = 1;
	return(m);
}

float	**rotation_y(float theta)
{
	float	**m;
	size_t	i;
	size_t	j;

	m = malloc(4 * sizeof(float *));
	i = 0;
	while (i < 4)
	{
		m[i] = malloc(4 * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m[i][j] = 0;
			j++;
		}
		i++;
	}
	m[0][0] = cos(theta);
	m[0][2] = sin(theta);
	m[1][1] = 1;
	m[2][2] = cos(theta);
	m[2][0] = -sin(theta);
	m[3][3] = 1;
	return(m);
}

float	**rotation_z(float theta)
{
	float	**m;
	size_t	i;
	size_t	j;

	m = malloc(4 * sizeof(float *));
	i = 0;
	while (i < 4)
	{
		m[i] = malloc(4 * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m[i][j] = 0;
			j++;
		}
		i++;
	}
	m[0][0] = cos(theta);
	m[0][1] = -sin(theta);
	m[1][0] = sin(theta);
	m[1][1] = cos(theta);
	m[2][2] = 1;
	m[3][3] = 1;
	return(m);
}
