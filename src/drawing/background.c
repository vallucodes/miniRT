#include "minirt.h"

void	reset_background(t_minirt *minirt)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < minirt->img->height)
	{
		j = 0;
		while (j < minirt->img->width)
		{
			mlx_put_pixel(minirt->img, j, i, minirt->map->background);
			j++;
		}
		i++;
	}
}
