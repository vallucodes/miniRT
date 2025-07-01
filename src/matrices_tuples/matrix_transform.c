#include "minirt.h"

void	matrix_fill_zero(t_matrix4 *m)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m->m[i][j] = 0;
			j++;
		}
		i++;
	}
}

t_matrix4	identity(void)
{
	t_matrix4	m;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				m.m[i][j] = 1;
			else
				m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	return (m);
}

t_matrix4	translation(float x, float y, float z)
{
	t_matrix4	m;

	matrix_fill_zero(&m);
	m.m[0][0] = 1;
	m.m[0][3] = x;
	m.m[1][1] = 1;
	m.m[1][3] = y;
	m.m[2][2] = 1;
	m.m[2][3] = z;
	m.m[3][3] = 1;
	return (m);
}

t_matrix4	scaling(float x, float y, float z)
{
	t_matrix4	m;

	matrix_fill_zero(&m);
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	m.m[3][3] = 1;
	return (m);
}
