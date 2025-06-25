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
	/*render_world(&minirt);
	mlx_loop_hook(minirt.mlx, &ft_keyhook, &minirt);
	mlx_loop(minirt.mlx);
	ft_lstclear(&minirt.world->objects, &free);
	close(minirt.world->fd);
	free(minirt.world);
	free(minirt.vp);*/

	//Testing parsing again after alterations.
	//fun_test_parsed_output(av, &minirt.world);

	/**
	 * Testing chapter 13 material
	 */
	test_cylinder();
	test_cylinder2();

	return (0);
}
//todo:DONE

//DONE:add max object amount = 100 in parsing stage
//DONE:add check in parsing that does not allow camera to be 0,0,0
