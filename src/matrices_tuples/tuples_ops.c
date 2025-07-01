#include "minirt.h"

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

t_tuple	scalar_divide_tuple(t_tuple tuple, float scalar) //never used
{
	t_tuple	new_tuple;

	new_tuple.x = tuple.x / scalar;
	new_tuple.y = tuple.y / scalar;
	new_tuple.z = tuple.z / scalar;
	new_tuple.w = tuple.w / scalar;
	return (new_tuple);
}
