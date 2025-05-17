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

//tuples
t_tuple	addition_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple substraction_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple negate_tuple(t_tuple tuple1);
t_tuple scalar_multiply_tuple(t_tuple tuple1, float scalar);
t_tuple scalar_divide_tuple(t_tuple tuple1, float scalar);
float	magnitude_tuple(t_tuple tuple);
t_tuple	normalize_tuple(t_tuple tuple);
float	dot_tuple(t_tuple tuple1, t_tuple tuple2);
t_tuple	cross_tuple(t_tuple tuple1, t_tuple tuple2);

//colors
t_color	addition_color(t_color color1, t_color color2);
t_color substraction_color(t_color color1, t_color color2);
t_color	multiply_color(t_color color1, t_color color2);


//matrices
bool	equality_matrix(float m1[4][4], float m2[4][4], size_t size);
float	**multiply_mtrx_by_mtrx(float m1[4][4], float m2[4][4], size_t size);
float	**multiply_mtrx_by_tuple(float m1[4][4], t_tuple t1, size_t size);
float	**transpose_matrix(float m1[4][4], size_t size);
int		determinant_matrix(float m1[3][3], size_t size);
float	**sub_matrix(float m1[4][4], int row, int col, size_t size);
int		minor_matrix(float m1[3][3], int row, int col, size_t size);
int		cofactor_matrix(float m1[3][3], int row, int col, size_t size);
float	**inverse_matrix(float m1[4][4], size_t size);

void	tick(t_env env, t_proj *proj);

int	is_equal(float a, float b);

#endif
