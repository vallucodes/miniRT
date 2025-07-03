/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:09:35 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/03 19:09:36 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
