#ifndef RAYTRACING_H
# define RAYTRACING_H

# define WIDTH 1000
# define HEIGHT	1000
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
	uint8_t		rgba[4];
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

typedef struct s_matrix4
{
	float m[4][4];
}	t_matrix4;

typedef struct s_matrix3
{
	float m[3][3];
}	t_matrix3;

typedef struct s_matrix2
{
	float m[2][2];
}	t_matrix2;
typedef struct s_matrix_ctx
{
	t_matrix4	m;
	size_t		size;
}	t_matrix_ctx;

typedef union s_matrix_union
{
	t_matrix2 m2;
	t_matrix3 m3;
} t_matrix_union;

typedef struct s_matrix_result
{
	t_matrix_union m;
	size_t size;
} t_matrix_result;

//Material light properties
typedef struct	s_material
{
	t_color	col;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}	t_material;

/**
 * @todo this is probably superfluous and redundant.
 */
/*typedef struct s_sphere
{
	t_tuple		center;
	float		radius;
	float		**transform;
	t_material	mat;
}	t_sphere;*/

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

typedef struct	s_comps
{
	bool		inside;
	t_scene_obj	*obj;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
}	t_comps;

//objects.c
t_scene_obj	sphere(t_minirt *minirt);
t_scene_obj	plane(t_minirt *minirt);

//lighting.c
t_light	init_point_light(t_tuple pos, t_color color, float ratio);
t_tuple	reflect(t_tuple in, t_tuple normal);
t_color	lighting(t_material m, t_light l, t_tuple p, t_tuple e_v, t_tuple n_v);

//normal.c
t_tuple	normal_at(t_minirt *minirt, t_scene_obj *obj, t_tuple point);

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
uint32_t	colour_unitrgb_hex(t_color c, float alpha);
void		colour_unitrgb_rgba(t_color *c);

//matrix math
bool		equality_matrix3(const t_matrix3 *a, const t_matrix3 *b);
bool		equality_matrix4(t_matrix4 m, t_matrix4 m2, size_t size);
t_matrix4	multiply_mtrx_by_mtrx(t_matrix4 m, t_matrix4 m2);
t_tuple		multiply_mtrx_by_tuple(t_matrix4 m, t_tuple t1);
t_matrix4	transpose_matrix(t_matrix4 m);
float		determinant_matrix4(t_matrix4 m);
float		determinant_matrix3(t_matrix3 m);
float		determinant_matrix2(t_matrix2 m);
t_matrix_result	sub_matrix(t_matrix_ctx *ctx, size_t row, size_t col);
float		minor_matrix(t_matrix_ctx *ctx, int row, int col);
float		cofactor_matrix(t_matrix_ctx *ctx, int row, int col);
t_matrix4	inverse_matrix(t_matrix4 m, bool *success);
bool		is_invertible_matrix4(t_matrix4 m);
bool		is_invertible_matrix3(t_matrix3 m);
bool		is_invertible_matrix2(t_matrix2 m);

//matrix operators
t_matrix4	identity(void);
t_matrix4	translation(int x, int y, int z);
t_matrix4	scaling(float x, float y, float z);
t_matrix4	rotation_x(float theta);
t_matrix4	rotation_y(float theta);
t_matrix4	rotation_z(float theta);

//matrix utils
void	matrix_fill_zero(t_matrix4 *m);

//rays
t_ray	create_ray(t_tuple vector, t_tuple point);
t_tuple	position_ray(t_ray ray, float t);
void	init_xs(t_xs *xs);
t_i		hit(t_xs *xs);
t_ray	transform(t_ray r, t_matrix4 m);
void	set_transform(t_scene_obj *obj, t_matrix4 m);
t_i		intersection(float intersection, void *obj);
void	intersections(t_xs	*xs, t_i i1, t_i i2);
t_xs	*intersect_world(t_minirt *minirt, t_ray r);

//shading
t_xs		*intersect_world(t_minirt *minirt, t_ray r);
t_comps		*prepare_computations(t_minirt *minirt, t_i i, t_ray r);
t_color		shade_hit(t_parse *world, t_comps *comps);
t_color		color_at(t_minirt *minirt, t_ray ray);

//camera
t_matrix4	view_transform(t_tuple from, t_tuple to, t_tuple up);
void	init_camera(t_minirt *minirt);
t_ray	ray_for_pixel(t_camera *c, int px, int py);
t_i		hit(t_xs *xs);

//intersections
t_xs	*intersects_sphere(t_scene_obj *obj, t_ray r, t_xs *xs);
t_xs	*intersect(t_scene_obj *obj, t_ray ray, t_xs *xs);

//utils
int			is_equal(float a, float b);
uint32_t	calculate_hit(t_minirt *minirt, size_t x, size_t y);

//print utils
void	print_ray(t_ray r);
void	print_xs(t_xs *xs);
void	print_matrix(t_matrix4 m, char *msg, int size);
void	print_tuple(t_tuple t);
void	print_colour(t_color c);
void	print_comps(t_comps *comps);
void	print_camera(t_camera *cam);
void	fun_test_parsed_output(char **av, t_parse *ps);

//dev
float	**create_matrix(size_t size, int flag);
void	unit_tests_3x3();
void	unit_tests_4x4();
void	unit_tests_transform_matrices();
void	test_normal_at_sphere(t_minirt *m);
void	test_reflect(t_minirt m);
void	test_reflect_extra(t_minirt m);
void	test_point_light_material();
void	test_point_light_reflections(void);
void	test_prepare_computations_outside(t_minirt *minirt, char **av);
void	test_prepare_computations_inside(t_minirt *minirt, char **av);
void	test_shading_an_intersection(t_minirt *minirt, char **av);
void	test_shading_an_intersection_from_inside(t_minirt *minirt, char **av);
void	test_ray_misses_obj(t_minirt *minirt);
void	test_ray_hits_obj(t_minirt *minirt);
void	test_intersection_behind_ray(t_minirt *minirt);
void	test_orientation(t_minirt *minirt);
void	test_camera(t_minirt *minirt);
void	test_ray_for_pixel(t_minirt *minirt);
void	test_intersect_two_spheres(t_minirt *minirt);
void	print_colour(t_color c);
void	test_shape(t_minirt *minirt);
void	test_intersect_generic(t_minirt *minirt);
void	test_plane_normal(t_minirt *minirt);
void	test_plane_intersect(t_minirt *minirt);
void	test_render_world(t_minirt *minirt);

#endif
