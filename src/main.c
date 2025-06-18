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
	// setbuf(stdout, NULL); //this was used just for debugging, when writing to file
	t_minirt minirt;
	t_parse	*ps;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ", STDERR_FILENO);
		ft_putstr_fd(av[0], STDERR_FILENO);
		ft_putstr_fd(" <scene file>.rt\n", STDERR_FILENO);
		return (1);
	}
	init_minirt(&minirt);
	ps = ft_calloc(1, sizeof(t_parse)); //null return is not always malloc fail
	// if (!ps)
		// exit_error();
	file_check(av, ps);
	if (!parsing_gateway(ps))
	{
		printf("Error\nExit, parsing failure.\n");
		exit (EXIT_FAILURE);
	}
	// fun_test_parsed_output(av, ps);
	minirt.world = ps;
	render_world(&minirt);
	mlx_loop_hook(minirt.mlx, &ft_keyhook, &minirt);
	mlx_loop(minirt.mlx);
	ft_lstclear(&ps->objects, &free);
	close(ps->fd);
	free(ps);
	free(minirt.vp);

	/**
	 * Testing chapter 9 material
	 */
	// test_shape(&minirt);
	//test_intersect_generic(&minirt);
	//test_plane_normal(&minirt);
	//test_plane_intersect(&minirt);

	return (0);
}
//todo

//add max object amount = 100
//add exit_error handling
