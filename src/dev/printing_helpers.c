#include "minirt.h"

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
	printf("t[w] = %f\n\n", t.w);
}

void	print_ray(t_ray r)
{
	printf("dir r[x] = %f\n", r.dir.x);
	printf("dir r[y] = %f\n", r.dir.y);
	printf("dir r[z] = %f\n", r.dir.z);
	printf("dir r[w] = %f\n", r.dir.w);
	printf("origin r[x] = %f\n", r.origin.x);
	printf("origin r[y] = %f\n", r.origin.y);
	printf("origin r[z] = %f\n", r.origin.z);
	printf("origin r[w] = %f\n", r.origin.w);
}
void	print_xs(t_xs *xs)
{
	printf("xs.count = %zu\n", xs->count);
	if (xs->object != NULL)
	{
		printf("xs.t[0] = %f\n", xs->t[0]);
		printf("xs.t[1] = %f\n\n", xs->t[1]);
	}
}
