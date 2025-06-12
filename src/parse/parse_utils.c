#include "../../inc/minirt.h"

/**
 * @todo RGB colours should be normalised to [0,1]
 */
void	parse_fill_colour(t_color *col, int r, int g, int b)
{
	col->r = (float)r / 255;
	col->g = (float)g / 255;
	col->b = (float)b / 255;
}

void	parse_fill_origin(t_tuple *origin, float cx, float cy, float cz)
{
	origin->x = cx;
	origin->y = cy;
	origin->z = cz;
	origin->w = 1;
}

void	parse_fill_norm(t_tuple *norm, float ox, float oy, float oz)
{
	norm->x = ox;
	norm->y = oy;
	norm->z = oz;
	norm->w = 0;
}

void	parse_fill_size(t_camera *camera)
{
	camera->hsize = WIDTH;
	camera->vsize = HEIGHT;
}
