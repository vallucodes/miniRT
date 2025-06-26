#include "minirt.h"

static inline void	swap_t_values(float *t)
{
	float	tmp;
	tmp = t[0];
	t[0] = t[1];
	t[1] = tmp;
}

/**
 * @brief Returns true if [r]ay intersects curved portion of cylinder.
 * @param [in] r: t_ray to be tested
 * @param [in] *q: t_quad - pointer to struct for quadratic values
 */
static bool	cylinder_discriminant(t_ray r, t_quad *q)
{
	q->a = (r.dir.x * r.dir.x) + (r.dir.z * r.dir.z);
	if (is_equal(q->a, 0))
		return (false);
	q->b = 2 * r.origin.x * r.dir.x + 2 * r.origin.z * r.dir.z;
	q->c = (r.origin.x * r.origin.x) + (r.origin.z * r.origin.z) - 1;
	q->d = (q->b * q->b) - 4 * q->a * q->c;
	if (q->d < 0)
		return (false);
	return (true);
}

/**
 * @brief Fill pointed xs with i1,i2 depending on actual cylinder intersections
 * @details This is to ensure we always pass 2 intersections to xs, regardless
 * 			of which intersections are filled or not
 */
static void	cylinder_fill_intersections(t_xs *xs, t_i i1, t_i i2)
{
	if (i1.object && i2.object)
		intersections(xs, i1, i2);
	else if (i1.object && !i2.object)
		intersections(xs, i1, i1);
	else if (i2.object && !i1.object)
		intersections(xs, i2, i2);
}

static bool	cylinder_check_cap(t_ray r, float t)
{
	float	x;
	float	z;
	float	res;

	x = r.origin.x + t * r.dir.x;
	z = r.origin.z + t * r.dir.z;
	res = (x * x) + (z * z);
	return (res <= 1);
}

t_xs	*cyl_intersect_caps(t_scene_obj *obj, t_xs *xs, t_ray r, t_i *i1, t_i *i2)
{
	float	t;

	if (is_equal(r.dir.y, 0) || obj->closed == false)
	{
		cylinder_fill_intersections(xs, *i1, *i2);
		return (xs);
	}
	t = (obj->min - r.origin.y) / r.dir.y;
	if (t > 0 && cylinder_check_cap(r, t))
		*i1 = intersection(t, obj);
	t = (obj->max - r.origin.y) / r.dir.y;
	if (t > 0 && cylinder_check_cap(r, t))
		*i2 = intersection(t, obj);
	cylinder_fill_intersections(xs, *i1, *i2);
	return (xs);
}

/**
 * @brief Add information to [xs] for given cylinder [obj] & [r]ay intersection
 * @todo will need breaking up for norm
 */
t_xs	*intersects_cylinder(t_scene_obj *obj, t_ray r, t_xs *xs)
{
	t_i		i1;
	t_i		i2;
	//t_i_t	*i;
	t_quad	q;
	float	t[2];
	float	y[2];

	//init_i_to_zeroes(i);
	init_i_to_zeroes(&i1,&i2);
	if (!cylinder_discriminant(r, &q))
		return (cyl_intersect_caps(obj, xs, r, &i1, &i2));
	t[0] = (-q.b - sqrt(q.d)) / (2 * q.a);
	t[1] = (-q.b + sqrt(q.d)) / (2 * q.a);
	if (t[0] > t[1])
		swap_t_values(t);
	y[0] = r.origin.y + t[0] * r.dir.y;
	if (obj->min < y[0] && y[0] < obj->max)
		i1 = intersection(t[0], obj);
	y[1] = r.origin.y + t[1] * r.dir.y;
	if (obj->min < y[1] && y[1] < obj->max)
		i2 = intersection(t[1], obj);


	cylinder_fill_intersections(xs, i1, i2);
	return (cyl_intersect_caps(obj, xs, r, &i1, &i2));
}
