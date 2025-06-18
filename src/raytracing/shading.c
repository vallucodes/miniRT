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
		intersect(obj, r, &xs);
		temp = temp->next;
		i++;
	}
	return (xs);
}

t_comps	*prepare_computations(t_i i, t_ray r)
{
	t_comps	*comps;

	comps = malloc(sizeof(t_comps));
	comps->obj = i.object;
	comps->point = position_ray(r, i.t);
	comps->eyev = normalize_tuple(negate_tuple(r.dir));
	comps->normalv = normal_at(comps->obj, comps->point);
	comps->over_point = addition_tuples(comps->point, scalar_multiply_tuple(comps->normalv, EPSILON));
	if (dot_tuple(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = negate_tuple(comps->normalv);
	}
	else
		comps->inside = false;
	return (comps);
}

t_color	shade_hit(t_parse *world, t_comps *comps, bool in_shadow)
{
	t_color	color = lighting(comps->obj->mat, world->lig_s, comps->over_point, comps->eyev, comps->normalv, in_shadow);
	return (color);
}

t_ray	get_ray_obj_to_light(t_minirt *minirt, t_tuple point, float	*distance)
{
	t_tuple	point_to_light;
	t_tuple	dir;
	t_light	*lig;

	lig = &minirt->world->lig_s;
	point_to_light = substraction_tuples(create_point(lig->cx, lig->cy, lig->cz),
						create_point(point.x, point.y, point.z));
	*distance = magnitude_tuple(point_to_light);
	dir = normalize_tuple(point_to_light);
	return (create_ray(dir, point));
}

bool	is_shadowed(t_minirt *minirt, t_tuple point, t_scene_obj *obj)
{
	t_ray	r;
	t_xs	xs;
	t_i		hit_p;
	float	distance;

	r = get_ray_obj_to_light(minirt, point, &distance);
	xs = intersect_world(minirt, r);
	hit_p = hit(&xs, obj);
	if (xs.count != 0 && hit_p.t < distance && hit_p.t > EPSILON)
		return (true);
	else
		return (false);
}


t_color	color_at(t_minirt *minirt, t_ray r)
{
	t_xs	xs;
	t_i		hit_p;
	t_comps	*comps;
	bool	in_shadow;
	t_color	color_var;

	xs = intersect_world(minirt, r);
	hit_p = hit(&xs, NULL);
	if (hit_p.object == NULL)
		return (color(0, 0, 0));
	comps = prepare_computations(hit_p, r);
	in_shadow = is_shadowed(minirt, comps->over_point, hit_p.object);
	color_var = shade_hit(minirt->world, comps, in_shadow);
	free(comps);
	return (color_var);
}

