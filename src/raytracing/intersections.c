#include "minirt.h"

t_i	intersection(float intersection, void *obj)
{
	t_i i;

	i.object = obj;
	i.t = intersection;
	return (i);
}

t_xs	*intersections(t_i i1, t_i i2)
{
	t_xs	*xs;

	xs = malloc(sizeof(t_xs));
	xs->count = 2;
	xs->object = malloc(xs->count * sizeof(void *));
	xs->t = malloc(xs->count * sizeof(float));
	xs->object[0] = i1.object;
	xs->object[1] = i2.object;
	xs->t[0] = i1.t;
	xs->t[1] = i2.t;
	//maybe needed sorting function here.
	return (xs);
}

// static	float magnitude(t_tuple t)
// {
// 	return (sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w));
// }

/**
 * @brief Returns intersection information for given sphere and ray 
 * @todo discriminant can probably be a function
 * 		 t_i may not be needed when we can just use a float
 */
t_xs	*intersects_sphere(t_minirt *minirt, t_scene_obj s, t_ray r)
{
	(void)minirt;
	t_i		i1;
	t_i		i2;
	// float	t1;
	// float	t2;
	// float	dir_len;
	t_xs	*xs;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_tuple	sphere_to_ray;

	//r = transform(r, inverse_matrix(minirt, s.transform, 4));
	sphere_to_ray = substraction_tuples(r.origin, create_point(0,0,0));
	a = dot_tuple(r.dir, r.dir);
	b = 2 * dot_tuple(sphere_to_ray, r.dir);
	c = dot_tuple(sphere_to_ray, sphere_to_ray) - s.radius * s.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		xs = malloc(sizeof(t_xs));
		xs->object = NULL;
		xs->t = NULL;
		xs->count = 0;
		return (xs);
	}
	i1 = intersection((-b - sqrt(discriminant)) / (2 * a), &s);
	i2 = intersection((-b + sqrt(discriminant)) / (2 * a), &s);
	xs = intersections(i1, i2);
	return (xs);
}

/**
 * @brief Returns intersection information for given [p]lane and [r]ay
 */
t_xs	*intersects_plane(t_minirt *minirt, t_scene_obj p, t_ray r)
{
	t_i		i1;
	float	t;
	t_xs	*xs;

	if (fabs(r.dir.y) < EPSILON)
	{
		xs->count = 0;
	}
	else
	{
		t = -r.origin.y / r.dir.y;
		i1 = intersection(t, &p);
		xs = intersections(i1, i1);
	}
	return (xs);
}

/**
 * @brief Returns intersection information. Selects intersection function. 
 * 		  Converts ray to current object space. 
 */
t_xs	*intersect(t_minirt *minirt, t_scene_obj *obj, t_ray ray)
{
	t_ray	local_ray;
	t_xs	*xs;

	local_ray = transform(ray, inverse_matrix(minirt, obj->transform, 4));
	obj->saved_ray.dir = local_ray.dir;
	obj->saved_ray.origin = local_ray.origin;
	if (obj->type == PLANE)
	{
		/* plane */
		xs = intersects_plane(minirt, *obj, local_ray);
	}
	else if (obj->type == SPHERE)
	{
		xs = intersects_sphere(minirt, *obj, local_ray);
	}
	else if (obj->type == CYLINDER)
	{
		/* cylinder */
	}
	return (xs);
}