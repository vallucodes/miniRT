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

t_i	hit_obj_to_light(t_xs *xs, t_scene_obj *obj_from)
{
	size_t	i;
	t_i		hit;
	t_scene_obj *obj_to;

	hit.t = -1;
	hit.object = NULL;
	i = 0;
	while(i < xs->count)
	{
		obj_to = xs->object[i];
		if (xs->t[i] > 0 && obj_to->id != obj_from->id)
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

t_ray	transform(t_ray r, t_matrix4 m)
{
	r.dir = multiply_mtrx_by_tuple(m, r.dir);
	r.origin = multiply_mtrx_by_tuple(m, r.origin);
	return (r);
}

/**
 * @brief Sets the transformation matrix of a t_scene_obj
 */
void	set_transform(t_scene_obj *object, t_matrix4 trans_mtrx)
{
	object->transform = trans_mtrx;
}

