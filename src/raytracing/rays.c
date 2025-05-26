#include "minirt.h"

t_ray	create_ray(t_tuple vector, t_tuple point)
{
	t_ray	ray;

	ray.origin = point;
	// print_tuple(ray.origin);
	ray.dir = vector;
	// print_tuple(ray.dir);
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

static	float magnitude(t_tuple t)
{
	return (sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w));
}

t_xs	*intersects_ray(t_minirt *minirt, t_sphere s, t_ray r)
{
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

	r = transform(r, inverse_matrix(minirt, s.transform, 4));
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

t_ray	transform(t_ray r, float **m)
{
	r.dir = multiply_mtrx_by_tuple(m, r.dir, 4);
	r.origin = multiply_mtrx_by_tuple(m, r.origin, 4);
	return (r);
}

void	set_transform(t_sphere *s, float **m)
{
	s->transform = m;
}
