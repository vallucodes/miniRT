#include "minirt.h"

t_comps	*prepare_computations(t_minirt *minirt, t_i i, t_ray r)
{
	t_comps	*comps;

	comps = malloc(sizeof(t_comps));
	comps->obj = i.object;
	comps->point = position_ray(r, i.t);
	comps->eyev = normalize_tuple(negate_tuple(r.dir));
	comps->normalv = normal_at_sphere(minirt, comps->obj, comps->point);
	return (comps);
}//this is segfaulting rn
