#include "../../inc/minirt.h"

/**
 * @todo RGB colours should be normalised to [0,1] 
 */
void	parse_fill_colour(t_color *col, int r, int g, int b)
{
	col->r = (float)r;
	col->g = (float)g;
	col->b = (float)b;
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
