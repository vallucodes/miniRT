#include "minirt.h"

void	projectile()
{
	t_env	env;
	t_proj	proj;

	env.g = create_vector(0, -0.3, 0);
	env.w = create_vector(-0.01, 0, 0);
	proj.pos = create_point(0, 1, 0);
	proj.v = create_vector(6, 11, 0);
	while (proj.pos.y > 0)
	{
		tick(env, &proj);
		printf("x: %f, y: %f\n", proj.pos.x, proj.pos.y);
	}
}

float	**create_matrix(size, flag)
{
	float	**m;
	int i = 0;

	m = malloc(sizeof(float *) * size);
	while (i < size)
	{
		m[i] = malloc(size * sizeof(float));
		// if (!m3[i])
			// cleanup_exit(arena);
		i++;
	}
	if (flag == 0)
	{
		m[0][0] =  9;  m[0][1] =  3;  m[0][2] =  0;  m[0][3] =  9;
		m[1][0] = -5;  m[1][1] = -2;  m[1][2] = -6;  m[1][3] = -3;
		m[2][0] = -4;  m[2][1] =  9;  m[2][2] =  6;  m[2][3] =  4;
		m[3][0] = -7;  m[3][1] =  6;  m[3][2] =  6;  m[3][3] =  2;
	}
	if (flag == 1)
	{
		m[0][0] = 1;  m[0][1] = 2;  m[0][2] = 3;  m[0][3] = 4;
		m[1][0] = 2;  m[1][1] = 4;  m[1][2] = 4;  m[1][3] = 2;
		m[2][0] = 8;  m[2][1] = 6;  m[2][2] = 4;  m[2][3] = 1;
		m[3][0] = 0;  m[3][1] = 0;  m[3][2] = 0;  m[3][3] = 1;
	}
	if (flag == 2)
	{
		m[0][0] = 1;  m[0][1] = 0;  m[0][2] = 0;  m[0][3] = 0;
		m[1][0] = 0;  m[1][1] = 1;  m[1][2] = 0;  m[1][3] = 0;
		m[2][0] = 0;  m[2][1] = 0;  m[2][2] = 1;  m[2][3] = 0;
		m[3][0] = 0;  m[3][1] = 0;  m[3][2] = 0;  m[3][3] = 1;
	}
	if (flag == 3)
	{
		m[0][0] = 2; m[0][1] = 9;
		m[1][0] = 3; m[1][1] = 90;
	}
	if (flag == 4)
	{
		m[0][0] =  1; m[0][1] =  2;  m[0][2] =  6;
		m[1][0] = -5; m[1][1] =  8;  m[1][2] = -4;
		m[2][0] =  2; m[2][1] =  6;  m[2][2] =  4;
	}
	return (m);
}

void	print_matrix(float **m, char *msg, int size)
{
	int i = 0;
	int j = 0;
	printf("Matrix %s\n", msg);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%8.5f ", m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}


void	print_tuple(t_tuple t)
{
	printf("t[x] = %f\n", t.x);
	printf("t[y] = %f\n", t.y);
	printf("t[z] = %f\n", t.z);
	printf("t[w] = %f\n", t.w);
}

int	main()
{

	float	**m0;
	float	**m1;
	float	**m2;
	float	**m3;
	t_tuple	t1;
	t_tuple	t2;

	m0 = create_matrix(4, 2);
	t1 = create_vector(1, 2, 3);
	t2 = multiply_mtrx_by_tuple(m0, t1, 4);
	print_tuple(t2);
}
