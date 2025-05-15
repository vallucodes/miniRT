/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:05:15 by elehtone          #+#    #+#             */
/*   Updated: 2025/05/15 13:08:01 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Function to free and NULL a pointer. Space saving.
 * @param [in] ptr: (void ptr)
*/
void	free_void(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

/**
 * @brief Frees and NULLs every array stored in matrix. Then frees the matrix.
 * @param [in] **matrix
 */
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free_void(matrix[i]);
		i++;
	}
	free_void(matrix);
}
