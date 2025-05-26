#include "minirt.h"

t_sphere	sphere(t_minirt *minirt)
{
	t_sphere	s;

	s.center = create_point(0, 0, 0);
	s.radius = 1.0;
	s.transform = identity(minirt);
	return (s);
}
