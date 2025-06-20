#include "minirt.h"

t_i	intersection(float intersection, void *obj)
{
	t_i i;

	i.object = obj;
	i.t = intersection;
	return (i);
}

void	intersections(t_xs *xs, t_i i1, t_i i2)
{
	xs->object[xs->count] = i1.object;
	xs->object[xs->count + 1] = i2.object;
	xs->t[xs->count] = i1.t;
	xs->t[xs->count + 1] = i2.t;
	xs->count += 2;
}

/**
 * @brief Returns intersection information for given sphere and ray
 * @todo discriminant can probably be a function
 */
t_xs	*intersects_sphere(t_scene_obj *obj, t_ray r, t_xs *xs)
{
	t_i		i1;
	t_i		i2;
	t_quad	q;
	t_tuple	sphere_to_ray;

	sphere_to_ray = substraction_tuples(r.origin, create_point(0,0,0));
	q.a = dot_tuple(r.dir, r.dir);
	q.b = 2 * dot_tuple(sphere_to_ray, r.dir);
	q.c = dot_tuple(sphere_to_ray, sphere_to_ray) - 1;
	q.d = q.b * q.b - 4 * q.a * q.c;
	if (q.d < 0)
		return (xs);
	i1 = intersection((-q.b - sqrt(q.d)) / (2 * q.a), obj);
	i2 = intersection((-q.b + sqrt(q.d)) / (2 * q.a), obj);
	intersections(xs, i1, i2);
	return (xs);
}

/**
 * @brief Returns intersection information for given [p]lane and [r]ay
 */
t_xs	*intersects_plane(t_scene_obj *p, t_ray r, t_xs *xs)
{
	t_i		i1;
	float	t;

	if (fabs(r.dir.y) < EPSILON)
	{
		return (xs);
		xs->count = 0;
	}
	else
	{
		t = -r.origin.y / r.dir.y;
		i1 = intersection(t, p);
		intersections(xs, i1, i1);
	}
	return (xs);
}

/**
 * @brief Returns intersection information. Selects intersection function.
 * 		  Converts ray to current object space.
 */
t_xs	*intersect(t_minirt *minirt, t_scene_obj *obj, t_ray ray, t_xs *xs)
{
	t_ray	local_ray;
	bool	success;

	local_ray = transform(ray, inverse_matrix(obj->transform, &success));
	if (!success)
		exit_error(minirt, INVERSE_MATRIX);
	obj->saved_ray.dir = local_ray.dir;
	obj->saved_ray.origin = local_ray.origin;
	if (obj->type == PLANE)
	{
		xs = intersects_plane(obj, local_ray, xs);
	}
	else if (obj->type == SPHERE)
	{
		xs = intersects_sphere(obj, local_ray, xs);
	}
	else if (obj->type == CYLINDER)
	{
		xs = intersects_cylinder(obj, local_ray, xs);
	}
	return (xs);
}
