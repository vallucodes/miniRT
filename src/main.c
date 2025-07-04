/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:11:47 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/04 12:35:12 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	t_minirt	minirt;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ", STDERR_FILENO);
		ft_putstr_fd(av[0], STDERR_FILENO);
		ft_putstr_fd(" <scene file>.rt\n", STDERR_FILENO);
		return (1);
	}
	init_minirt(&minirt);
	minirt.world = ft_calloc(1, sizeof(t_parse));
	if (!minirt.world)
		exit_error(&minirt, MALLOC);
	file_check(av, minirt.world);
	if (!parsing_gateway(minirt.world))
	{
		exit_error(&minirt, NULL);
		minirt.world = NULL;
	}
	render_world(&minirt);
	mlx_loop_hook(minirt.mlx, &ft_keyhook, &minirt);
	mlx_loop(minirt.mlx);
	cleanup(&minirt);
	return (0);
}
