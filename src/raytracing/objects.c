#include "minirt.h"

/**
 * @brief Create and give attributes to a sphere object 
 * @returns t_sphere object 
 */
t_sphere	sphere(t_minirt *minirt)
{
	t_sphere	s;

	s.center = create_point(0, 0, 0);
	s.radius = 1.0;
	s.transform = identity(minirt);
	s.mat = init_material();
	return (s);
}
