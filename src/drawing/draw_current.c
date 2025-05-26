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
	xs = intersects_ray(minirt, s, r);
	// print_xs(xs);
	if (xs->count != 0)
		return (minirt->map->colored);
	else
		return (minirt->map->background);
}

uint32_t	get_color_from_ray(t_minirt *minirt)
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
	return (0);
}


void	draw_current_thing(t_minirt *minirt)
{
	// size_t		i;
	// size_t		j;
	// uint32_t	color;
	get_color_from_ray(minirt);
	// i = 0;
	// while (i < HEIGHT)
	// {
	// 	j = 0;
	// 	while (j < WIDTH)
	// 	{
	// 		color = get_color_from_ray(i, j);
	// 		mlx_put_pixel(minirt->img, j, i, color);
	// 		j++;
	// 	}
	// 	i++;
	// }
}

// void draw_circle(t_minirt *minirt)
// {
// 	int cx = 800;
// 	int cy = 400;
// 	int r = 200;
// 	int x = r;
// 	int y = 0;
// 	int d = 1 - r;

// 	while (x >= y)
// 	{
// 		int i = -x;
// 		while (i <= x)
// 		{
// 			mlx_put_pixel(minirt->img, cx + i, cy + y, minirt->map->colored);
// 			mlx_put_pixel(minirt->img, cx + i, cy - y, minirt->map->colored);
// 			i++;
// 		}

// 		i = -y;
// 		while (i <= y)
// 		{
// 			mlx_put_pixel(minirt->img, cx + i, cy + x, minirt->map->colored);
// 			mlx_put_pixel(minirt->img, cx + i, cy - x, minirt->map->colored);
// 			i++;
// 		}

// 		y++;
// 		if (d < 0)
// 			d += 2 * y + 1;
// 		else
// 		{
// 			x--;
// 			d += 2 * (y - x) + 1;
// 		}
// 	}
// }


// uint32_t	projectile(t_minirt *minirt, size_t i, size_t j)
// {
// 	t_env	env;
// 	t_proj	proj;

// 	env.g = create_vector(0, 0.8, 0);
// 	env.w = create_vector(0.80, 0, 0);
// 	proj.pos = create_point(0, HEIGHT - 1, 0);
// 	proj.v = create_vector(9, -20, 0);
// 	while (proj.pos.y < HEIGHT)
// 	{
// 		tick(env, &proj);
// 		if ((int)proj.pos.y < HEIGHT && (int)proj.pos.y > 0 &&
// 			(int)proj.pos.x < WIDTH && (int)proj.pos.x > 0)
// 		{
// 			int px = (int)proj.pos.x;
// 			int py = (int)proj.pos.y;
// 			int size = 3;

// 			int dx = -size;
// 			while (dx <= size)
// 			{
// 				int dy = -size;
// 				while (dy <= size)
// 				{
// 					int x = px + dx;
// 					int y = py + dy;
// 					if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 						mlx_put_pixel(minirt->img, x, y, minirt->map->colored);
// 					dy++;
// 				}
// 				dx++;
// 			}
// 		}
// 	}
// 	return (0);
// }
