#ifndef RAYTRACING_H
# define RAYTRACING_H

# define WIDTH	500
# define HEIGHT	250
# define MALLOC	"Memory allocation failed"

//Material default values
# define amb_default 0.1
# define dif_default 0.9
# define spec_default 0.9
# define shine_default 200

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

/**
 * @brief Colour tuple arithmetic operations only act on r,g,b
 */
typedef struct s_color
{
	float		r;
	float		g;
	float		b;
	float		a;
	uint8_t		rgba[3];
	uint32_t	hex;
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

typedef struct s_matrix_ctx
{
	t_minirt	*minirt;
	float		**m;
	size_t		size;
}	t_matrix_ctx;

//Material light properties
typedef struct	s_material
{
	t_color	col;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}	t_material;

typedef struct s_sphere
{
	t_tuple		center;
	float		radius;
	float		**transform;
	t_material	mat;
}	t_sphere;

typedef struct	s_light_vars
{
	t_color	eff_col;
	t_color	amb_col;
	t_color	dif_col;
	t_color	spec_col;
	t_tuple	light_vec;
	t_tuple	reflect_vec;
	float	l_dot_n;
	float	r_dot_e;
	float	fac;
}	t_light_vars;

//objects.c
t_sphere	sphere(t_minirt *minirt);

//lighting.c
t_light	init_point_light(t_tuple pos, t_color color, float ratio);
t_tuple	normal_at_sphere(t_minirt *minirt, t_scene_obj *obj, t_tuple p);
t_tuple	reflect(t_tuple in, t_tuple normal);

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
t_color		addition_color(t_color color1, t_color color2);
t_color 	substraction_color(t_color color1, t_color color2);
t_color		multiply_color(t_color color1, t_color color2);
t_color		multiply_color_scalar(t_color col, float sca);
uint32_t	colour_unitrgb_hex(t_color c, uint8_t alpha);

//matrix math
bool	equality_matrix(float **m, float **m2, size_t size);
float	**multiply_mtrx_by_mtrx(t_minirt *minirt, float **m, float **m2, size_t size);
t_tuple	multiply_mtrx_by_tuple(float **m, t_tuple t1, size_t size);
float	**transpose_matrix(t_minirt *minirt, float **m, size_t size);
float	determinant_matrix(t_minirt *minirt, float **m, size_t size);
float	**sub_matrix(t_matrix_ctx *ctx, size_t row, size_t col);
float	minor_matrix(t_matrix_ctx *ctx, int row, int col);
float	cofactor_matrix(t_matrix_ctx *ctx, int row, int col);
bool	is_invertible_matrix(t_minirt *minirt, float **m, size_t size);
float	**inverse_matrix(t_minirt *minirt, float **m, size_t size);

//matrix operators
float	**identity(t_minirt *minirt);
float	**translation(t_minirt *minirt, int x, int y, int z);
float	**scaling(t_minirt *minirt, float x, float y, float z);
float	**rotation_x(t_minirt *minirt, float theta);
float	**rotation_y(t_minirt *minirt, float theta);
float	**rotation_z(t_minirt *minirt, float theta);

//matrix utils
float	**matrix_alloc(t_minirt *minirt, size_t size);

//rays
t_ray	create_ray(t_tuple vector, t_tuple point);
t_tuple	position_ray(t_ray ray, float t);
t_xs	*intersects_ray(t_minirt *minirt, t_scene_obj *obj, t_ray r, t_xs *xs);
void	init_xs(t_xs *xs);
t_i		hit(t_xs *xs);
t_ray	transform(t_ray r, float **m);
void	set_transform(t_scene_obj *obj, float **m);
void	intersections(t_xs	*xs, t_i i1, t_i i2);
t_xs	*intersect_world(t_minirt *minirt, t_ray r);

//utils
int			is_equal(float a, float b);
uint32_t	calculate_hit(t_minirt *minirt, size_t x, size_t y);

//dev
void	fun_test_parsed_output(char **av, t_parse *ps);
void	print_matrix(float **m, char *msg, int size);
void	print_tuple(t_tuple t);
float	**create_matrix(size_t size, int flag);
void	print_ray(t_ray r);
void	print_xs(t_minirt *minirt, t_xs *xs);
void	unit_tests_3x3(t_minirt *minirt);
void	unit_tests_4x4(t_minirt *minirt);
void	unit_tests_transform_matrices(t_minirt *minirt);
void	test_rotation_z_matrix(t_minirt *minirt);
void	test_rotation_y_matrix(t_minirt *minirt);
void	test_rotation_x_matrix(t_minirt *minirt);
void	test_scaling_matrix(t_minirt *minirt);
void	test_normal_at_sphere(t_minirt *m);
void	test_reflect(t_minirt m);
void	test_reflect_extra(t_minirt m);
void	test_point_light_material();
void	test_point_light_reflections(void);
void	test_intersect_two_spheres(t_minirt *minirt, char **av);
void	print_colour(t_color c);

#endif
