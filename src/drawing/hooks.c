#include "minirt.h"

void	draw_hook(void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	reset_background(minirt);
	// draw_current_thing(minirt);
}
