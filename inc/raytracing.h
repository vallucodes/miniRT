#ifndef RAYTRACING_H
# define RAYTRACING_H

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_env
{
	t_tuple	g;
	t_tuple w;
}	t_env;

typedef struct s_proj
{
	t_tuple	pos;
	t_tuple v;
}	t_proj;

t_tuple	create_vector(float x, float y, float z);
t_tuple	create_point(float x, float y, float z);
t_tuple	addition_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple substraction_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple negate_tuple(t_tuple tuple1);
t_tuple scalar_multiply_tuple(t_tuple tuple1, float scalar);
t_tuple scalar_divide_tuple(t_tuple tuple1, float scalar);
float	magnitude_tuple(t_tuple tuple);
t_tuple	normalize_tuple(t_tuple tuple);
float	dot_tuple(t_tuple tuple1, t_tuple tuple2);
t_tuple	cross_tuple(t_tuple tuple1, t_tuple tuple2);

t_color	addition_color(t_color color1, t_color color2);
t_color substraction_color(t_color color1, t_color color2);

void	tick(t_env env, t_proj *proj);

int	is_equal(float a, float b);

#endif
