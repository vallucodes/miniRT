#include "minirt.h"

t_xs	*intersect_world(t_minirt *minirt, t_ray r)
{
	t_xs	*xs;
	int		i;
	t_list	*temp = minirt->world->objects;

	xs = malloc(sizeof(t_xs));
	init_xs(xs);
	i = 0;
	while (i < minirt->world->obj_count)
	{
		t_scene_obj *obj = (t_scene_obj *)temp->content;
		intersect(obj, r, xs);
		temp = temp->next;
		i++;
	}
	return (xs);
}

t_comps	*prepare_computations(t_minirt *minirt, t_i i, t_ray r)
{
	t_comps	*comps;

	comps = malloc(sizeof(t_comps));
	comps->obj = i.object;
	comps->point = position_ray(r, i.t);
	comps->eyev = normalize_tuple(negate_tuple(r.dir));
	comps->normalv = normal_at(minirt, comps->obj, comps->point);
	if (dot_tuple(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = negate_tuple(comps->normalv);
	}
	else
		comps->inside = false;
	return (comps);
}

t_color	shade_hit(t_parse *world, t_comps *comps)
{
	t_color	color = lighting(comps->obj->mat, world->lig_s, comps->point, comps->eyev, comps->normalv);
	return (color);
}

t_color	color_at(t_minirt *minirt, t_ray r)
{
	t_xs	*xs = intersect_world(minirt, r);
	t_i		hit_p = hit(xs);
	if (hit_p.object == NULL)
		return (color(0, 0, 0));
	t_comps *comps = prepare_computations(minirt, hit_p, r);
	t_color color = shade_hit(minirt->world, comps);
	return (color);
}


