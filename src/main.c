#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	// setbuf(stdout, NULL); //this was used just for debugging, when writing to file
	t_minirt	minirt;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ", STDERR_FILENO);
		ft_putstr_fd(av[0], STDERR_FILENO);
		ft_putstr_fd(" <scene file>.rt\n", STDERR_FILENO);
		return (1);
	}
	init_minirt(&minirt);
	minirt.world = ft_calloc(1, sizeof(t_parse)); //null return is not always malloc fail
	if (!minirt.world)
		exit_error(&minirt, MALLOC);
	file_check(av, minirt.world);
	if (!parsing_gateway(minirt.world))
	{
		minirt.world = NULL;
		exit_error(&minirt, NULL);
	}
	// fun_test_parsed_output(av, ps);
	render_world(&minirt);
	mlx_loop_hook(minirt.mlx, &ft_keyhook, &minirt);
	mlx_loop(minirt.mlx);
	ft_lstclear(&minirt.world->objects, &free);
	close(minirt.world->fd);
	free(minirt.world);
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

//add max object amount = 100 in parsing stage
//add check in parsing that does not allow camera to be 0,0,0
