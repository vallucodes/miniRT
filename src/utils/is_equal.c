#include "minirt.h"

inline bool	is_equal(float a, float b)
{
	float	res;

	res = fabs(a - b);
	if (res < EPSILON)
		return (true);
	return (false);
}
