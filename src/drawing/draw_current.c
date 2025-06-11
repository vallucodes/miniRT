#include "minirt.h"

t_tuple	hit_point(t_ray r, t_xs *xs)
{
	float	t_hit;
	t_i		hit_var;
	t_tuple	hit_point;

	hit_var = hit(xs);
	t_hit = hit_var.t;
	hit_point = position_ray(r, t_hit);
	return (hit_point);
}

/**
 * @todo A lot of declarations here will be replaced by parsed rt information
 */
uint32_t	calculate_hit(t_minirt *minirt, size_t x, size_t y)
{
	t_ray	r;
	t_xs	*xs;
	t_scene_obj obj;
	float **m;

	//Converting between pixel space to viewport space. Raster, NDC etc.
	//handling camera location and ray creation
	float Px = (x + 0.5) * minirt->vp->vp_w / WIDTH - minirt->vp->vp_w / 2;
	float Py = (y + 0.5) * minirt->vp->vp_h / HEIGHT - minirt->vp->vp_h / 2;
	t_tuple	point_on_vp = create_point(Px, Py, -1);
	t_tuple	camera_pos = create_point(0, 0, -5);
	t_tuple dir = normalize_tuple(substraction_tuples(point_on_vp, camera_pos));
	r = create_ray(dir, camera_pos);

	//object creation, transform, material and colour (@todo parsed)
	//obj = sphere(minirt);		//sphere test (@todo parsed)
	obj = plane(minirt);		//plane test (@todo parsed)

	obj.mat.col = color(1, 0.94, 0);
	//m = multiply_mtrx_by_mtrx(minirt, rotation_z(minirt, M_PI / 3), scaling(minirt, 1, 0.5, 1), 4);
	m = rotation_x(minirt, -0.1);
	//m = identity(minirt);
	set_transform(&obj, m);


	//light creation, location, colour (@todo parsed)
	t_light light;
	light = init_point_light(create_point(-15, -15, -15), color(1, 1, 1), 1);

	xs = intersect(minirt, &obj, r);
	// print_xs(xs);
	if (xs->count != 0)
	{
		t_tuple point			= hit_point(r, xs);
		t_tuple normal			= normal_at(minirt, &obj, point);
		t_color	res				= lighting(obj.mat, light, point, negate_tuple(r.dir), normal);
		uint32_t	hex_colour	= colour_unitrgb_hex(res, 1);
		return (hex_colour);
	}
	else
		return (minirt->map->background);
}

void	draw_current_thing(t_minirt *minirt)
{
	size_t		x;
	size_t		y;
	uint32_t	color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			color = calculate_hit(minirt, x, y);
			mlx_put_pixel(minirt->img, x, y, color);
			y++;
		}
		x++;
	}
}
