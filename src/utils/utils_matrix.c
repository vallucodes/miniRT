#include "../../inc/minirt.h"

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
