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

t_sx	intersects_ray(t_sphere s, t_ray r)
{
	t_sx	sx;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_tuple	sphere_to_ray;

	sphere_to_ray = substraction_tuples(r.origin, create_point(0,0,0));
	sx.count = 0;
	sx.t[0] = 0;
	sx.t[1] = 0;
	a = dot_tuple(r.dir, r.dir);
	b = 2 * dot_tuple(sphere_to_ray, r.dir);
	c = dot_tuple(sphere_to_ray, sphere_to_ray) - s.radius * s.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (sx);
	sx.count = 2;
	sx.t[0] = (-b - sqrt(discriminant)) / (2 * a);
	sx.t[1] = (-b + sqrt(discriminant)) / (2 * a);
	return (sx);
}
