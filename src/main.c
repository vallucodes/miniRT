#include "minirt.h"

int	main()
{
	t_tuple	vector1;
	t_tuple	vector2;
	t_tuple	point1;
	t_tuple	point2;

	vector1 = create_vector(3, 2, 1);
	vector2 = create_vector(5, 6, 7.0);
	point1 = create_point(3, 2, 1);
	point2 = create_point(5, 6, 7);
	printf("vector1 xyzw: %f, %f, %f, %f\n", vector1.x, vector1.y, vector1.z, vector1.w);
	printf("vector2 xyzw: %f, %f, %f, %f\n", vector2.x, vector2.y, vector2.z, vector2.w);
	printf("point1 xyzw: %f, %f, %f, %f\n", point1.x, point1.y, point1.z, point1.w);
	printf("point2 xyzw: %f, %f, %f, %f\n", point2.x, point2.y, point2.z, point2.w);
	printf("x and y are equal: %i\n", is_equal(vector1.x, vector1.y));
	t_tuple	vector3 = substraction_tuples(vector1, vector2);
	printf("subs xyzw: %f, %f, %f, %f\n", vector3.x, vector3.y, vector3.z, vector3.w);

}
