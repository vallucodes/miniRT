#include "../inc/minirt.h"

void fun_test_parsed_output(char **av, t_parse *ps);

int	main(int ac, char **av)
{
	t_parse	*ps;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./minirt <scene file>.rt\n", STDERR_FILENO);
		return (1);
	}
	ps = ft_calloc(1, sizeof(t_parse));
	file_check(av, ps);

	parsing_gateway(ps);

	fun_test_parsed_output(av, ps);

	return (0);
}

void fun_test_parsed_output(char **av, t_parse *ps)
{
	printf("Infile: %s\n\n", av[1]);

	printf("Printing default optical objects:\n");
	printf("\nAmbient light settings:\n");
	printf("Count: %i | Ratio: %f | RGB: %i, %i, %i", ps->amb_b, ps->amb_s.ratio, ps->amb_s.r, ps->amb_s.g, ps->amb_s.b);

	printf("\n\nDiffuse light settings:\n");
	printf("Count: %i | Ratio: %f | Pos: %f, %f, %f", ps->lig_b, ps->lig_s.ratio, ps->lig_s.cx, ps->lig_s.cy, ps->lig_s.cz);
	
	printf("\n\nCamera settings:\n");
	printf("Count: %i | FOV: %i | Pos: %f, %f, %f | Nor: %f, %f, %f\n", ps->cam_b, ps->cam_s.fov, ps->cam_s.cx, ps->cam_s.cy, ps->cam_s.cz, ps->cam_s.ox, ps->cam_s.oy, ps->cam_s.oz);
}