#include "minirt.h"

void	projectile()
{
	t_env	env;
	t_proj	proj;

	env.g = create_vector(0, -0.3, 0);
	env.w = create_vector(-0.01, 0, 0);
	proj.pos = create_point(0, 1, 0);
	proj.v = create_vector(60, 110, 0);
	while (proj.pos.y > 0)
	{
		tick(env, &proj);
		printf("x: %f, y: %f\n", proj.pos.x, proj.pos.y);
	}
}

void	set_colors(t_minirt *minirt)
{
	minirt->map->background = 0xFFC067BB;
	minirt->map->colored = 0xFF000000;
}



void	init_minirt(t_minirt *minirt)
{
	t_map *map;

	minirt->map = malloc(sizeof(t_map));
	// if (!minirt->map)
		// exit_error();
	set_colors(minirt);
	minirt->mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	// if (!minirt->mlx)
		// exit_error(minirt.map, NULL, 0, mlx_strerror(mlx_errno));
	minirt->img = mlx_new_image(minirt->mlx, WIDTH, HEIGHT);
	if (!minirt->img || (mlx_image_to_window(minirt->mlx, minirt->img, 0, 0) < 0))
	{
		mlx_close_window(minirt->mlx);
		// exit_error(minirt.map, NULL, 0, mlx_strerror(mlx_errno));
	}
}

int	main()
{
	float	**m0;
	float	**m1;
	float	**m2;
	float	**m3;
	t_tuple	t1;
	t_tuple	t2;
	t_tuple	t3;
	t_ray	r;
	t_i		i;
	t_xs	*xs;
	t_sphere s; //edit this to int maybe
	t_minirt minirt;

	init_minirt(&minirt);
	t2 = create_point(0, 0, -5);
	t1 = create_vector(0, 0, 1);
	r = create_ray(t1, t2);
	print_tuple(t1);
	print_tuple(t2);
	s = sphere(); //needs to return unique value?
	xs = intersects_ray(s, r);
	printf("count %zu, int[0] %f, int[1] %f\n", xs->count, xs->t[0], xs->t[1]);
	i = hit(xs);
	// mlx_loop_hook(minirt.mlx, &draw_hook, &minirt);
	// mlx_loop(minirt.mlx);
}
