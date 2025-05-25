#include "minirt.h"

t_sphere	sphere(void)
{
	t_sphere	s;

	s.center = create_point(0, 0, 0);
	s.radius = 1.0;
	s.transform = identity();
	return (s);
}
