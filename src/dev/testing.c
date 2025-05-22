#include "minirt.h"

void	testing()
{
	float	**matrix1;
	float	**matrix2;
	float	**matrix3;
	float	**matrix4;
	float	**T1;
	float	**T2;
	float	**m3;
	t_tuple	t1;
	t_tuple	t2;
	t_tuple	t3;
	t_ray	r;
	t_i		i;
	t_xs	*xs;
	t_sphere s; //edit this to int maybe

	t2 = create_point(1, 0, 1);
	matrix1 = rotation_x(M_PI / 2);
	matrix2 = scaling(5, 5, 5);
	matrix3 = translation(10, 5, 7);
	T1 = multiply_mtrx_by_mtrx(matrix1, identity(), 4);
	T2 = multiply_mtrx_by_mtrx(matrix2, T1, 4);
	matrix4 = multiply_mtrx_by_mtrx(matrix3, T2, 4);
	t2 = multiply_mtrx_by_tuple(matrix4, t2, 4);
	print_tuple(t2);
}
