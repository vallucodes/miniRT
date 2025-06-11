#include "minirt.h"

int	is_equal(float a, float b)
{
	float	res;

	res = a - b;
	if (res < 0)
		res = -res;
	if (res < EPSILON)
		return (true);
	return (false);
}
