#include "minirt.h"

float	magnitude_tuple(t_tuple tuple)
{
	float	magnitude;

	magnitude = sqrtf(tuple.x * tuple.x +
					tuple.y * tuple.y +
					tuple.z * tuple.z +
					tuple.w * tuple.w);
	return (magnitude);
}

t_tuple	normalize_tuple(t_tuple tuple)
{
	t_tuple	new_tuple;

	new_tuple.x = tuple.x / magnitude_tuple(tuple);
	new_tuple.y = tuple.y / magnitude_tuple(tuple);
	new_tuple.z = tuple.z / magnitude_tuple(tuple);
	new_tuple.w = tuple.w / magnitude_tuple(tuple);
	return (new_tuple);
}

float	dot_tuple(t_tuple tuple1, t_tuple tuple2)
{
	float	dot;

	dot = tuple1.x * tuple2.x +
			tuple1.y * tuple2.y +
			tuple1.z * tuple2.z;
	return (dot);
}

t_tuple	cross_tuple(t_tuple tuple1, t_tuple tuple2)
{
	return (create_vector(tuple1.y * tuple2.z - tuple1.z * tuple2.y,
						tuple1.z * tuple2.x - tuple1.x * tuple2.z,
						tuple1.x * tuple2.y - tuple1.y * tuple2.x));
}
