#ifndef RAYTRACING_H
# define RAYTRACING_H

typedef struct s_point_vector
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

t_tuple	create_vector(float x, float y, float z);
t_tuple	create_point(float x, float y, float z);
t_tuple	addition_tuples(t_tuple *tuple1, t_tuple *tuple2);
t_tuple substraction_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple negate_tuple(t_tuple tuple1);

int	is_equal(float a, float b);

#endif
