#ifndef TUPLE_H
# define TUPLE_H

# include <math.h>
# include <stdbool.h>
# include <stdio.h>

# define epsilon 0.00001

typedef struct t_tuple
{
	double	x;
	double	y;
	double	z;
	float	w;
}	t_tuple;

//maths_helpers.c
bool	floats_are_equal(double n1, double n2);

//tuple_create.c
t_tuple	tuple_init(double x, double y, double z, double w);
t_tuple	tuple_from_vector(double *vec);
t_tuple	tuple_from_point(double *point);

//tuple_info.c
void	tuple_print(t_tuple tuple);
bool	tuple_is_vector(t_tuple tuple);
bool	tuple_is_vector(t_tuple tuple);
double	tuple_magnitude(t_tuple tuple);
t_tuple	tuple_normalise(t_tuple tuple);

//tuple_arithmetic.c
//bool	tuples_are_equal(float *t1, float *t2);
t_tuple	tuple_add(t_tuple l, t_tuple r);
t_tuple	tuple_sub(t_tuple l, t_tuple r);
t_tuple tuple_neg(t_tuple tuple);
double	tuple_dot(t_tuple l, t_tuple r);
t_tuple	tuple_cross(t_tuple l, t_tuple r);

//tuple_scalar_arithmetic.c
t_tuple tuple_mult(t_tuple l, double fac);
t_tuple tuple_div(t_tuple l, double div);


#endif