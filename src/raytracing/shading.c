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

t_comps	*prepare_computations(t_i i, t_ray r)
{
	t_comps	*comps;

	comps = malloc(sizeof(t_comps));
	comps->obj = i.object;
	comps->point = position_ray(r, i.t);
	comps->eyev = normalize_tuple(negate_tuple(r.dir));
	comps->normalv = normal_at(comps->obj, comps->point);
	comps->over_point = addition_tuples(comps->point, scalar_multiply_tuple(comps->normalv, EPSILON));
	// printf("point\n");
	// print_tuple(comps->point);
	// printf("overpoint\n");
	// print_tuple(comps->over_point);
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

bool	is_shadowed(t_minirt *minirt, t_tuple point)
{
	t_ray	r;
	t_tuple	dir;
	t_xs	*xs;
	t_i		hit_p;
	// printf("light point:\n");
	// printf("x %f, y %f, z %f\n", minirt->world->lig_s.cx, minirt->world->lig_s.cy, minirt->world->lig_s.cz);
	// printf("t_tuple point:\n");
	// print_tuple(point);
	t_tuple	v = substraction_tuples(create_point(minirt->world->lig_s.cx, minirt->world->lig_s.cy, minirt->world->lig_s.cz), create_point(point.x, point.y, point.z));

	float	distance = magnitude_tuple(v);
	dir = normalize_tuple(v);
	r = create_ray(dir, point);
	xs = intersect_world(minirt, r);
	// print_xs(xs);
	hit_p = hit(xs);
	// printf("hit %f\n", hit_p.t);
	// printf("xs->count %zu, hit_p.t %f, distance %f\n", xs->count, hit_p.t, distance);
	if (xs->count != 0 && hit_p.t < distance && hit_p.t > 0)
		return (true);
	else
		return (false);
}

bool	is_shadowed_testing(t_minirt *minirt, t_tuple point, t_scene_obj *obj)
{
	t_ray	r;
	t_tuple	dir;
	t_xs	*xs;
	t_i		hit_p;
	// printf("light point:\n");
	// printf("x %f, y %f, z %f\n", minirt->world->lig_s.cx, minirt->world->lig_s.cy, minirt->world->lig_s.cz);
	// printf("t_tuple point:\n");
	// print_tuple(point);
	t_tuple	v = substraction_tuples(create_point(minirt->world->lig_s.cx, minirt->world->lig_s.cy, minirt->world->lig_s.cz), create_point(point.x, point.y, point.z));
	// if (obj->type == PLANE)
	// {
	// 	printf("vector from point to light:\n");
	// 	print_tuple(v);
	// }

	float	distance = magnitude_tuple(v);
	dir = normalize_tuple(v);
	r = create_ray(dir, point);
	xs = intersect_world(minirt, r);
	// print_xs(xs);
	hit_p = hit_obj_to_light(xs, obj);
	// if (obj->type == PLANE)
	// {
	// 	printf("hit %f\n", hit_p.t);
	// 	printf("xs->count %zu, hit_p.t %f, distance %f\n", xs->count, hit_p.t, distance);
	// }
	if (xs->count != 0 && hit_p.t < distance && hit_p.t > 0)
		return (true);
	else
		return (false);
}

t_color	color_at(t_minirt *minirt, t_ray r)
{
	t_xs	*xs = intersect_world(minirt, r);
	t_i		hit_p = hit(xs);
	if (hit_p.object == NULL)
		return (color(0, 0, 0));
	t_comps *comps = prepare_computations(hit_p, r);
	// t_scene_obj *obj = (t_scene_obj *)hit_p.object;
	bool	in_shadow = is_shadowed_testing(minirt, comps->over_point, hit_p.object);
	// if (in_shadow == 1)
		// printf("yes\n");
	// bool	in_shadow = 0;
	t_color color = shade_hit(minirt->world, comps, in_shadow);
	free(xs);
	return (color);
}


