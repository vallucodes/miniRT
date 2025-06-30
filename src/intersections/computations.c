#include "minirt.h"

t_xs	intersect_world(t_minirt *minirt, t_ray r)
{
	t_xs		xs;
	int			i;
	t_scene_obj	*obj;
	t_list		*temp;

	init_xs(&xs);
	temp = minirt->world->objects;
	i = 0;
	while (i < minirt->world->obj_count)
	{
		obj = (t_scene_obj *)temp->content;
		intersect(minirt, obj, r, &xs);
		temp = temp->next;
		i++;
	}
	return (xs);
}
t_i	hit(t_xs *xs, t_scene_obj *obj_from)
{
	size_t		i;
	t_i			hit;
	t_scene_obj	*obj_to;

	hit.t = -1;
	hit.object = NULL;
	i = 0;
	while(i < xs->count)
	{
		obj_to = xs->object[i];
		if (xs->t[i] > 0 && (!obj_from || obj_to->id != obj_from->id))
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

t_comps	prepare_computations(t_minirt *minirt, t_i i, t_ray r)
{
	t_comps	comps;

	comps.obj = i.object;
	comps.point = position_ray(r, i.t);
	comps.eyev = normalize_tuple(negate_tuple(r.dir));
	comps.normalv = normal_at(minirt, comps.obj, comps.point);
	comps.over_point = addition_tuples(comps.point, scalar_multiply_tuple(comps.normalv, EPSILON));
	if (dot_tuple(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tuple(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}
