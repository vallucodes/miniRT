#include "minirt.h"

int	main()
{
	t_env	env;
	t_proj	proj;

	env.g = create_vector(0, -0.1, 0);
	env.w = create_vector(-0.01, 0, 0);
	proj.pos = create_point(0, 1, 0);
	proj.v = create_vector(1, 11, 0);
	while (proj.pos.y > 0)
	{
		tick(env, &proj);
		printf("x: %f, y: %f\n", proj.pos.x, proj.pos.y);
	}
	// printf("vector1 xyzw: %f, %f, %f, %f\n", v1.x, v1.y, v1.z, v1.w);
	// printf("vector2 xyzw: %f, %f, %f, %f\n", v2.x, v2.y, v2.z, v2.w);
	// printf("point1 xyzw: %f, %f, %f, %f\n", p1.x, p1.y, p1.z, p1.w);
	// printf("point2 xyzw: %f, %f, %f, %f\n", p2.x, p2.y, p2.z, p2.w);
	// printf("x and y are equal: %i\n", is_equal(v1.x, v1.y));
	// t_tuple	v3 = scalar_divide_tuple(p1, 2);
	// printf("scalar div xyzw: %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);
	// float mag = magnitude_tuple(v2);
	// printf("magnitude %f\n", mag);
	// v3 = normalize_tuple(v2);
	// mag = magnitude_tuple(v3);
	// printf("normalize vec xyzw: %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);
	// printf("magnitude %f\n", mag);
	// float dot = dot_tuple(v1, v2);
	// printf("dot %f\n", dot);
	// v3 = cross_tuple(v2, v1);
	// printf("cross v1 v2 vec xyzw: %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);





}
