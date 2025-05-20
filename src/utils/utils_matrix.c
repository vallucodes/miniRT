#include "../../inc/minirt.h"

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
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}
