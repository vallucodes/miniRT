#include "minirt.h"

uint32_t	get_color_from_ray(t_minirt *minirt)
{
	size_t	i;
	float **m;
	float **m1;
	float **m2;
	float **m3;
	t_tuple p[12];

	m2 = translation(0, -200, 0);
	m = rotation_z(2 * M_PI / 6);
	m3 = translation(700, 600, 0);

	i = 0;
	while (i < 12)
	{
		p[i] = create_point(0, 0, 0);
		m = rotation_z(i * M_PI / 6);
		p[i] = multiply_mtrx_by_tuple(m2, p[i], 4);
		p[i] = multiply_mtrx_by_tuple(m, p[i], 4);
		p[i] = multiply_mtrx_by_tuple(m3, p[i], 4);
		if ((int)p[i].y < HEIGHT && (int)p[i].y > 0 &&
			(int)p[i].x < WIDTH && (int)p[i].x > 0)
		{
			int px = (int)p[i].x;
			int py = (int)p[i].y;
			int size = 3;

			int dx = -size;
			while (dx <= size)
			{
				int dy = -size;
				while (dy <= size)
				{
					int x = px + dx;
					int y = py + dy;
					if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
						mlx_put_pixel(minirt->img, x, y, minirt->map->colored);
					dy++;
				}
				dx++;
			}
		}
		i++;
	}
	return (0);
}


void	draw_current_thing(t_minirt *minirt)
{
	// size_t		i;
	// size_t		j;
	uint32_t	color;
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
