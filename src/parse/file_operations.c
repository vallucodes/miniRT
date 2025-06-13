#include "../../inc/minirt.h"

/**
 * @brief Open the given file and report if opening fails. 
 * @return EXIT_FAILURE on fail, proper fd on success. 
 */
int	file_check(char **av, t_parse *ps)
{
	ps->fd = open(av[1], O_RDONLY);
	if (ps->fd == -1)
	{
		perror("Error\nScene file open failed: ");
		exit(EXIT_FAILURE);
	}
	return (ps->fd);
}
