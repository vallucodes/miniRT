#include "minirt.h"

t_ray	create_ray(t_tuple vector, t_tuple point)
{
	t_ray	ray;

	ray.origin = point;
	ray.dir = vector;
	return (ray);
}

t_tuple	position_ray(t_ray ray, float t)
{
	t_tuple	new_vector;

	new_vector = addition_tuples(scalar_multiply_tuple(ray.dir, t), ray.origin);
	return (new_vector);
}

t_i	hit(t_xs *xs)
{
	size_t	i;
	t_i		hit;

	hit.t = -1;
	hit.object = NULL;
	i = 0;
	while(i < xs->count)
	{
		if (xs->t[i] > 0)
		{
			if (hit.t == -1 || xs->t[i] < hit.t)
			{
				hit.t = xs->t[i];
				hit.object = xs->object[i];
			}
		}
		i++;
	}
	return(hit);
}

t_i	intersection(int intersection, void *obj)
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
	xs->count = 4;
	xs->object = malloc(xs->count * sizeof(char));
	xs->t = malloc(xs->count * sizeof(float));
	xs->object[0] = i1.object;
	xs->object[1] = i2.object;
	xs->t[0] = i1.t;
	xs->t[1] = i2.t;
	return (xs);
}

t_xs	*intersects_ray(t_sphere s, t_ray r)
{
	t_i		i1;
	t_i		i2;
	t_xs	*xs;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_tuple	sphere_to_ray;

	sphere_to_ray = substraction_tuples(r.origin, create_point(0,0,0));
	a = dot_tuple(r.dir, r.dir);
	b = 2 * dot_tuple(sphere_to_ray, r.dir);
	c = dot_tuple(sphere_to_ray, sphere_to_ray) - s.radius * s.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (NULL);
	i1 = intersection((-b - sqrt(discriminant)) / (2 * a), &s);
	i2 = intersection((-b + sqrt(discriminant)) / (2 * a), &s);
	xs = intersections(i1, i2);
	return (xs);
}
