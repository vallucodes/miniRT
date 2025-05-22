#include "minirt.h"

int	is_equal(float a, float b)
{
	float	epsilon;
	float	res;

	epsilon = 0.00001;
	res = a - b;
	if (res < 0)
		res = -res;
	if (res < epsilon)
		return (true);
	return (false);
}
