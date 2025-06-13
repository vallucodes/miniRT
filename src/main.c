#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	t_minirt minirt;
	init_minirt(&minirt);

	t_parse	*ps;
	ps = ft_arena_calloc(minirt.arena, 1, sizeof(t_parse), alignof(t_parse));

	if (ac != 2)
		exit_wrong_params(av);
	file_check(av, ps);
	if (!parsing_gateway(ps))
	{
		printf("Error\nExit, parsing failure.\n");
		exit (EXIT_FAILURE);
	}
fun_test_parsed_output(av, ps);
	minirt.world = ps;
	// free(ps);
	// test_ray_for_pixel(&minirt);
	render_world(&minirt);
	// mlx_loop_hook(minirt.mlx, &draw_hook, &minirt); //dont activate this hook. Its insanely slow because raytracing is very heavy process and this is redrawing everything every frame
	mlx_loop(minirt.mlx);
	close(ps->fd);
	ft_lstclear(&ps->objects, &free);

	/**
	 * Testing chapter 9 material
	 */
	// test_shape(&minirt);
	//test_intersect_generic(&minirt);
	//test_plane_normal(&minirt);
	//test_plane_intersect(&minirt);

	return (0);
}

//restriction to be added, allow max amount of objects. Currently this is determining 1000 objects max and 1000 intersections per ray max
// xs->object = malloc(1000 * sizeof(void *));
// xs->t = malloc(1000 * sizeof(float));
