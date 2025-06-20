#include "minirt.h"

static void	init_i(t_i *i)
{
	i->t = 0;
	i->object = NULL;
}

/**
 * @brief Returns intersection information for given cylinder and ray
 * @todo will need breaking up for norm
 */
t_xs	*intersects_cylinder(t_scene_obj *obj, t_ray r, t_xs *xs)
{
	t_i		i1;
	t_i		i2;
	t_quad	q;
	float	t[2];
	float	y[2];

	init_i(&i1);
	init_i(&i2);
	q.a = (r.dir.x * r.dir.x) + (r.dir.z * r.dir.z);
	if (fabs(q.a) < EPSILON)
		return (xs);
	q.b = 2 * r.origin.x * r.dir.x + 2 * r.origin.z * r.dir.z;
	q.c = (r.origin.x * r.origin.x) + (r.origin.z * r.origin.z) - 1;
	q.d = (q.b * q.b) - 4 * q.a * q.c;
	if (q.a < EPSILON)
		return (xs);
	t[0] = (-q.b - sqrt(q.d)) / (2 * q.a);
	t[1] = (-q.b + sqrt(q.d)) / (2 * q.a);
	if (t[0] > t[1])
		{
			float	a = t[0];
			t[0] = t[1];
			t[1] = a;
		}
	y[0] = r.origin.y + t[0] * r.dir.y;
	if (obj->min < y[0] && y[0] < obj->max)
		i1 = intersection(t[0], obj);
	y[1] = r.origin.y + t[1] * r.dir.y;
	if (obj->min < y[1] && y[1] < obj->max)
		i2 = intersection(t[1], obj);
	if (i1.object && i2.object)
		intersections(xs, i1, i2);
	else if (i1.object && !i2.object)
		intersections(xs, i1, i1);
	else if (i2.object && !i1.object)
		intersections(xs, i2, i2);
	return (xs);
}

