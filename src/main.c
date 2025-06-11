#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	t_minirt minirt;
	init_minirt(&minirt);

	/*t_parse	*ps;
	ps = ft_arena_calloc(minirt.arena, 1, sizeof(t_parse), alignof(t_parse));

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./minirt <scene file>.rt\n", STDERR_FILENO);
		return (1);
	}
	file_check(av, ps);
	// ps = ft_calloc(1, sizeof(t_parse));
	if (!parsing_gateway(ps))
	{
		printf("exit, parsing failure\n");
		exit (EXIT_FAILURE);
	}
	minirt.world = ps;
	// fun_test_parsed_output(av, ps);
	// free(ps);
	// test_intersect_two_spheres(&minirt);
	draw_current_thing(&minirt);
	// mlx_loop_hook(minirt.mlx, &draw_hook, &minirt); //dont activate this hook. Its insanely slow because raytracing is very heavy process and this is redrawing everything every frame
	mlx_loop(minirt.mlx);
	close(ps->fd);
	ft_lstclear(&ps->objects, &free);*/

	/**
	 * Testing chapter 9 material
	 */
	//test_shape(&minirt);
	//test_intersect_generic(&minirt);
	//test_plane_normal(&minirt);
	test_plane_intersect(&minirt);

	return (0);
}

