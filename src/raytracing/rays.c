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

t_i	intersects_ray(t_sphere s, t_ray r)
{
	t_i	i;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_tuple	sphere_to_ray;
	size_t	i;

	sphere_to_ray = substraction_tuples(r.origin, create_point(0,0,0));
	a = dot_tuple(r.dir, r.dir);
	b = 2 * dot_tuple(sphere_to_ray, r.dir);
	c = dot_tuple(sphere_to_ray, sphere_to_ray) - s.radius * s.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (i);
	i.t[0] = (-b - sqrt(discriminant)) / (2 * a);
	i.t[1] = (-b + sqrt(discriminant)) / (2 * a);
	i.object = 's';
	// i.t = malloc(i.count * sizeof(char));
	// i = 0;
	// while (i < i.count)
	// {
	// 	i.t[i] = 's';
	// 	i++;
	// }
	return (i);
}
