#ifndef RAYTRACING_H
# define RAYTRACING_H

# define WIDTH	1500
# define HEIGHT	1000
# define MALLOC	"Memory allocation failed"
typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	dir;
}	t_ray;
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

//dev
typedef struct s_proj
{
	t_tuple	pos;
	t_tuple v;
}	t_proj;

typedef struct s_sphere
{
	t_tuple	center;
	float	radius;
}	t_sphere;

typedef struct s_i
{
	float	t;
	void	*object;
}	t_i;

typedef struct s_xs
{
	size_t	count;
	void	**object;
	float	*t;
}	t_xs;

//tuples
t_tuple	create_vector(float x, float y, float z);
t_tuple	create_point(float x, float y, float z);

//tuple operations
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
bool	equality_matrix(float **m, float **m2, size_t size);
float	**multiply_mtrx_by_mtrx(float **m1, float **m2, size_t size);
t_tuple	multiply_mtrx_by_tuple(float **m, t_tuple t1, size_t size);
float	**transpose_matrix(float **m, size_t size);
float	determinant_matrix(float **m, size_t size);
float	**sub_matrix(float **m, size_t row, size_t col, size_t size);
float	minor_matrix(float **m, int row, int col, size_t size);
float	cofactor_matrix(float **m, int row, int col, size_t size);
bool	is_invertible_matrix(float **m, size_t size);
float	**inverse_matrix(float **m, size_t size);

//rays
t_ray	create_ray(t_tuple vector, t_tuple point);
t_tuple	position_ray(t_ray ray, float t);
t_xs	*intersects_ray(t_sphere s, t_ray r);
t_i		hit(t_xs *xs);

//objects
t_sphere	sphere(void);

//utils
int		is_equal(float a, float b);

//dev
void	tick(t_env env, t_proj *proj);
void	print_matrix(float **m, char *msg, int size);
void	print_tuple(t_tuple t);
float	**create_matrix(size_t size, int flag);

#endif
