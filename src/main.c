#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	t_parse ps;

	if (ac != 2)
	{
		ft_putstr_fd("Exiting: Usage: ./miniRT <scene file>.rt", STDERR_FILENO);
		return 1;
	}
	
	if (file_check(av, ps) == -1)
	{
		ft_putstr_fd("Exiting: Scene file failed filesystem checks.", STDERR_FILENO);
		return 1;
	}


	parsing_gateway(ac, av);
	
	return 0;
}
