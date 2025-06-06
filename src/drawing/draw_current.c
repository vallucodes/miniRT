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

uint32_t	calculate_hit(t_minirt *minirt, size_t x, size_t y)
{
	t_ray	r;
	t_xs	*xs;
	t_sphere s; //edit this to int maybe
	float **m;

	//Converting between pixel space to viewport space. Raster, NDC etc.
	//handling camera location and ray creation
	float Px = (x + 0.5) * minirt->vp->vp_w / WIDTH - minirt->vp->vp_w / 2;
	float Py = (y + 0.5) * minirt->vp->vp_h / HEIGHT - minirt->vp->vp_h / 2;
	t_tuple	point_on_vp = create_point(Px, Py, -1);
	t_tuple	camera_pos = create_point(0, 0, -5);
	t_tuple dir = normalize_tuple(substraction_tuples(point_on_vp, camera_pos));
	r = create_ray(dir, camera_pos);

	//sphere creation, transform, material and colour
	s = sphere(minirt);
	s.mat.col = color(1, 0.2, 1);
	m = multiply_mtrx_by_mtrx(minirt, rotation_z(minirt, M_PI / 4), scaling(minirt, 0.5, 1, 1), 4);
	set_transform(&s, m);

	//light creation, location, colour
	t_light light;
	light = init_point_light(create_point(-10, -10, -10), color(1, 1, 1), 1);

	xs = intersects_ray(minirt, s, r);
	// print_xs(xs);
	if (xs->count != 0)
	{
		t_tuple point			= hit_point(r, xs);
		t_tuple normal			= normal_at_sphere(minirt, s, point);
		t_color	res				= lighting(s.mat, light, point, negate_tuple(r.dir), normal);
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
