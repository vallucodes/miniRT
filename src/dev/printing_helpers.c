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
