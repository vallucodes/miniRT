#include "minirt.h"

void	cleanup(t_minirt *minirt)
{
	if (minirt->world != NULL)
	{
		ft_lstclear(&minirt->world->objects, &free);
		close(minirt->world->fd);
	}
	if (minirt->mlx != NULL)
		mlx_close_window(minirt->mlx);
	free(minirt->world);
	free(minirt->vp);
}

void	exit_error(t_minirt *minirt, const char *msg)
{
	if (msg != NULL)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putendl_fd((char *)msg, STDERR_FILENO);
	}
	cleanup(minirt);
	exit(1);
}
