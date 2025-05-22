#include "minirt.h"

void	tick(t_env env, t_proj *proj)
{
	proj->pos = addition_tuples(proj->pos, proj->v);
	proj->v = addition_tuples(addition_tuples(proj->v, env.g), env.w);
}
