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

void	init_xs(t_xs *xs)
{
	xs->count = 0;
}

/**
 * @brief Returns intersection information for given sphere and ray
 * @todo discriminant can probably be a function
 */
t_xs	*intersects_sphere(t_scene_obj *obj, t_ray r, t_xs *xs)
{
	t_i		i1;
	t_i		i2;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_tuple	sphere_to_ray;

	sphere_to_ray = substraction_tuples(r.origin, create_point(0,0,0));
	a = dot_tuple(r.dir, r.dir);
	b = 2 * dot_tuple(sphere_to_ray, r.dir);
	c = dot_tuple(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (xs);
	i1 = intersection((-b - sqrt(discriminant)) / (2 * a), obj);
	i2 = intersection((-b + sqrt(discriminant)) / (2 * a), obj);
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
 * @brief Returns intersection information for given cylinder and ray
 * @todo discriminant can probably be a function
 */
t_xs	*intersects_cylinder(t_scene_obj *obj, t_ray r, t_xs *xs)
{
	t_i		i1[2];
	t_i		i2[2];
	float	abcd[4];
	float	y[2];

	abcd[0] = (r.dir.x * r.dir.x) + (r.dir.z * r.dir.z);
	if (0 - fabs(abcd[0]) < EPSILON)
		return (xs);
	else
	{
		abcd[1] = 2 * r.origin.x * r.dir.x + 2 * r.origin.z * r.dir.z;
		abcd[2] = (r.origin.x * r.origin.x) + (r.origin.z * r.origin.z) - 1;
		abcd[3] = (abcd[1] * abcd[1]) - 4 * abcd[0] * abcd[2];
		if (abcd[3] < 0)
			return (xs);
		i1[0] = intersection((-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]), obj);
		i2[0] = intersection((-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]), obj);
	}
	y[0] = r.origin.y + i1[0].t * r.dir.y;
	if (obj->min < y[0] && y[0] < obj->max)
		i1[1] = i1[0];
	y[1] = r.origin.y + i2[0].t * r.dir.y;
	if (obj->min < y[1] && y[1] < obj->max)
		i2[1] = i2[0];
	intersections(xs, i1[1], i2[1]);
	return (xs);
}

/**
 * @brief Returns intersection information. Selects intersection function.
 * 		  Converts ray to current object space.
 */
t_xs	*intersect(t_scene_obj *obj, t_ray ray, t_xs *xs)
{
	t_ray	local_ray;
	bool	success;

	local_ray = transform(ray, inverse_matrix(obj->transform, &success));
	// if (!success)
	// 	error_exit(minirt);
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
