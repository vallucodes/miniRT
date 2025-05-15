#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	t_parse ps;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./miniRT <scene file>.rt\n", STDERR_FILENO);
		return 1;
	}
	file_check(av, ps);

	parsing_gateway(ps);
	
	return 0;
}
