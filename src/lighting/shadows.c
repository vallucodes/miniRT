#include "minirt.h"

static t_ray	get_ray_obj_to_light(t_minirt *minirt, t_tuple point, float	*distance)
{
	t_tuple	point_to_light;
	t_tuple	dir;
	t_light	*lig;

	lig = &minirt->world->lig_s;
	point_to_light = substraction_tuples(create_point(lig->cx, lig->cy, lig->cz),
						create_point(point.x, point.y, point.z));
	*distance = magnitude_tuple(point_to_light);
	if (*distance == 0)
		dir = create_vector(0, 0, 1);
	else
		dir = normalize_tuple(point_to_light);
	return (create_ray(dir, point));
}

bool	is_shadowed(t_minirt *minirt, t_tuple point, t_scene_obj *obj)
{
	t_ray	r;
	t_xs	xs;
	t_i		hit_p;
	float	distance;

	r = get_ray_obj_to_light(minirt, point, &distance);
	xs = intersect_world(minirt, r);
	hit_p = hit(&xs, obj);
	if (xs.count != 0 && hit_p.t < distance && hit_p.t > EPSILON)
		return (true);
	else
		return (false);
}
