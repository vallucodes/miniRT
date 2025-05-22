#include "minirt.h"

void	testing(void)
{
	float	**m1;
	float	**m2;
	float	**m3;
	float	**m4;
	float	**T1;
	float	**T2;
	t_tuple	t1;
	t_tuple	t2;
	t_tuple	t3;
	t_ray	r;
	t_ray	r2;
	t_i		i;
	t_xs	*xs;
	t_sphere s; //edit this to int maybe

	r = create_ray(create_vector(0, 0, 1), create_point(2, 0, -5)); //play around with this more
	s = sphere();
	set_transform(&s, scaling(2, 2, 1));
	xs = intersects_ray(s, r);
	print_xs(xs);
}
