/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:56:04 by elehtone          #+#    #+#             */
/*   Updated: 2025/07/03 21:56:09 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * @brief Report incorrect usage error and exit with failure 
 */
void	exit_wrong_params(char **av)
{
	ft_putstr_fd("Error\nUsage: ", STDERR_FILENO);
	ft_putstr_fd(av[0], STDERR_FILENO);
	ft_putstr_fd(" <scene file>.rt\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
