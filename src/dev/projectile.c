#include "minirt.h"

void	projectile()
{
	t_env	env;
	t_proj	proj;

	env.g = create_vector(0, -0.3, 0);
	env.w = create_vector(-0.01, 0, 0);
	proj.pos = create_point(0, 1, 0);
	proj.v = create_vector(60, 110, 0);
	while (proj.pos.y > 0)
	{
		tick(env, &proj);
		printf("x: %f, y: %f\n", proj.pos.x, proj.pos.y);
	}
}
