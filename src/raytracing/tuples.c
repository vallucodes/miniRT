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
	t_tuple	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	new_vector.w = 1;
	return (new_vector);
}

t_tuple	addition_tuples(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	new_tuple;

	new_tuple.x = tuple1->x + tuple2->x;
	new_tuple.y = tuple1->y + tuple2->y;
	new_tuple.z = tuple1->z + tuple2->z;
	new_tuple.w = tuple1->w + tuple2->w;
	return(new_tuple);
}

t_tuple substraction_tuples(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	new_tuple;

	new_tuple.x = tuple1.x - tuple2.x;
	new_tuple.y = tuple1.y - tuple2.y;
	new_tuple.z = tuple1.z - tuple2.z;
	new_tuple.w = tuple1.w - tuple2.w;
	return(new_tuple);
}

t_tuple negate_tuple(t_tuple tuple1)
{
	t_tuple	new_tuple;

	new_tuple.x = -tuple1.x;
	new_tuple.y = -tuple1.y;
	new_tuple.z = -tuple1.z;
	new_tuple.w = -tuple1.w;
	return(new_tuple);
}
