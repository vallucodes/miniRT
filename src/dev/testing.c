#include "minirt.h"

uint32_t	calculate_hit(t_minirt *minirt, size_t x, size_t y)
{
	float	**m1;
	float	**m2;
	float	**m3;
	float	**m4;
	float	**T1;
	float	**T2;
	float	a;
	float	b;
	t_tuple	t1;
	t_tuple	t2;
	t_tuple	t3;
	t_ray	r;
	t_ray	r2;
	t_i		i;
	t_xs	*xs;
	t_sphere s; //edit this to int maybe

	float aspect_ratio = (float)WIDTH / (float)HEIGHT;
	float fov = M_PI / 2;
	float vp_h = 2.0f * tan(fov / 2);
	float vp_w = aspect_ratio * vp_h;

	float Px = (x + 0.5) * vp_w / WIDTH - vp_w / 2;
	float Py = (y + 0.5) * vp_h / HEIGHT - vp_h / 2;
	t_tuple	point_on_vp = create_point(Px, Py, -1);
	t_tuple	camera_pos = create_point(0, 0, -5);
	t_tuple dir = normalize_tuple(substraction_tuples(point_on_vp, camera_pos));
	r = create_ray(dir, camera_pos);
	s = sphere();
	set_transform(&s, scaling(1, 1, 1));
	xs = intersects_ray(s, r);
	// print_xs(xs);
	if (xs->count != 0)
		return (minirt->map->colored);
	else
		return (minirt->map->background);
}


// float aspect_ratio = (float)WIDTH / (float)HEIGHT;
// float fov = M_PI / 2.0; // 90 degrees, adjust as needed
// float scale = tan(fov * 0.5);

// float Px = (2 * ((x + 0.5) / (float)WIDTH) - 1) * aspect_ratio * scale;
// float Py = (1 - 2 * ((y + 0.5) / (float)HEIGHT)) * scale;

// t_tuple pixel_on_plane = create_point(Px, Py, -1);
// t_tuple camera_origin = create_point(0, 0, 0);
// t_tuple dir = normalize(subtract(pixel_on_plane, camera_origin));
// t_ray r = create_ray(dir, camera_origin);















