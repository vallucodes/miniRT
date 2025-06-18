#include "minirt.h"

t_tuple	create_vector(float x, float y, float z)
{
	t_tuple	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	new_vector.w = 0;
	return (new_vector);
}

t_tuple	create_point(float x, float y, float z)
{
	t_tuple	new_point;

	new_point.x = x;
	new_point.y = y;
	new_point.z = z;
	new_point.w = 1;
	return (new_point);
}

t_tuple	addition_tuples(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	new_tuple;

	new_tuple.x = tuple1.x + tuple2.x;
	new_tuple.y = tuple1.y + tuple2.y;
	new_tuple.z = tuple1.z + tuple2.z;
	new_tuple.w = tuple1.w + tuple2.w;
	return (new_tuple);
}

t_tuple	substraction_tuples(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	new_tuple;

	new_tuple.x = tuple1.x - tuple2.x;
	new_tuple.y = tuple1.y - tuple2.y;
	new_tuple.z = tuple1.z - tuple2.z;
	new_tuple.w = tuple1.w - tuple2.w;
	return (new_tuple);
}

t_tuple	negate_tuple(t_tuple tuple)
{
	t_tuple	new_tuple;

	new_tuple.x = -tuple.x;
	new_tuple.y = -tuple.y;
	new_tuple.z = -tuple.z;
	new_tuple.w = -tuple.w;
	return (new_tuple);
}

t_tuple	scalar_multiply_tuple(t_tuple tuple, float scalar)
{
	t_tuple	new_tuple;

	new_tuple.x = tuple.x * scalar;
	new_tuple.y = tuple.y * scalar;
	new_tuple.z = tuple.z * scalar;
	new_tuple.w = tuple.w * scalar;
	return (new_tuple);
}

t_tuple	scalar_divide_tuple(t_tuple tuple, float scalar)
{
	t_tuple	new_tuple;

	new_tuple.x = tuple.x / scalar;
	new_tuple.y = tuple.y / scalar;
	new_tuple.z = tuple.z / scalar;
	new_tuple.w = tuple.w / scalar;
	return (new_tuple);
}

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
	return(new_tuple);
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
