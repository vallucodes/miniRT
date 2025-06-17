#include "../inc/minirt.h"

void	set_ids_for_objects(t_list *objects)
{
	t_scene_obj	*obj;
	size_t		i;

	obj = NULL;
	i = 0;
	while (objects != NULL)
	{
		obj = objects->content;
		obj->id = i;
		i++;
		objects = objects->next;
	}
}

int	main(int ac, char **av)
{
	t_minirt minirt;
	init_minirt(&minirt);

	t_parse	*ps;
	ps = ft_arena_calloc(minirt.arena, 1, sizeof(t_parse), alignof(t_parse));

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ", STDERR_FILENO);
		ft_putstr_fd(av[0], STDERR_FILENO);
		ft_putstr_fd(" <scene file>.rt\n", STDERR_FILENO);
		return (1);
	}
	file_check(av, ps);
	if (!parsing_gateway(ps))
	{
		printf("Error\nExit, parsing failure.\n");
		exit (EXIT_FAILURE);
	}
	// fun_test_parsed_output(av, ps);
	minirt.world = ps;
	set_ids_for_objects(minirt.world->objects);
	// free(ps);
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

//restriction to be added, allow max amount of objects. Currently this is determining 100 objects max and 200 intersections per ray max
// xs->object = malloc(200 * sizeof(void *));
// xs->t = malloc(200 * sizeof(float));
