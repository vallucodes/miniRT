#include "minirt.h"

int	main()
{
	t_tuple	v1;
	t_tuple	v2;
	t_tuple	p1;
	t_tuple	p2;

	v1 = create_vector(1, 2, 3);
	v2 = create_vector(2, 3, 4);
	p1 = create_point(3, 2, -1);
	p2 = create_point(5, 6, 7);
	printf("vector1 xyzw: %f, %f, %f, %f\n", v1.x, v1.y, v1.z, v1.w);
	printf("vector2 xyzw: %f, %f, %f, %f\n", v2.x, v2.y, v2.z, v2.w);
	printf("point1 xyzw: %f, %f, %f, %f\n", p1.x, p1.y, p1.z, p1.w);
	printf("point2 xyzw: %f, %f, %f, %f\n", p2.x, p2.y, p2.z, p2.w);
	printf("x and y are equal: %i\n", is_equal(v1.x, v1.y));
	t_tuple	v3 = scalar_divide_tuple(p1, 2);
	printf("scalar div xyzw: %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);
	float mag = magnitude_tuple(v2);
	printf("magnitude %f\n", mag);
	v3 = normalize_tuple(v2);
	mag = magnitude_tuple(v3);
	printf("normalize vec xyzw: %f, %f, %f, %f\n", v3.x, v3.y, v3.z, v3.w);
	printf("magnitude %f\n", mag);
	float dot = dot_tuple(v1, v2);
	printf("dot %f\n", dot);

}
