/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:12:46 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/03 23:25:34 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# define WIDTH			400
# define HEIGHT			400
# define MAX_OBJECTS	100
# define MALLOC			"Memory allocation failed"
# define PARSING		"Exit, parsing failure."
# define SHAPE			"Unreachable code: shape unrecognized."
# define INVERSE_MATRIX	"Matrix not invertible."

//Material default values
# define DIF_DEFAULT 0.9
# define SPEC_DEFAULT 0.9
# define SHINE_DEFAULT 200

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
	t_tuple	w;
}	t_env;

typedef struct s_i
{
	float	t;
	void	*object;
}	t_i;

typedef struct	s_i_t
{
	t_i	i1;
	t_i	i2;
}	t_i_t;

typedef struct s_xs
{
	size_t	count;
	void	*object[MAX_OBJECTS * 2];
	float	t[MAX_OBJECTS];
}	t_xs;

typedef struct s_quad
{
	float	a;
	float	b;
	float	c;
	float	d;
}	t_quad;

//Material light properties
typedef struct	s_material
{
	t_color	col;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}	t_material;

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
	bool	skip;
}	t_light_vars;

typedef struct	s_comps
{
	bool		inside;
	t_scene_obj	*obj;
	t_tuple		point;
	t_tuple		over_point;
	t_tuple		eyev;
	t_tuple		normalv;
}	t_comps;

typedef struct	s_row_copy_params
{
	size_t src_row;
	size_t dest_row;
	size_t skip_col;
}	t_row_copy_params;

typedef struct	s_calc_vars
{
	float	xoffset;
	float	yoffset;
	float	view_port_x;
	float	view_port_y;
}	t_calc_vars;

typedef struct	s_calc_vars2
{
	t_matrix4	k;
	t_matrix4	k2;
	t_matrix4	r;
	t_matrix4	first_term;
	t_matrix4	second_term;
	t_matrix4	third_term;
}	t_calc_vars2;

typedef struct	s_normal_vars
{
	t_tuple		local_point;
	t_tuple		local_normal;
	t_tuple		world_normal;	
}	t_normal_vars;

typedef struct	s_is
{
	t_i	i1;
	t_i	i2;
}	t_is;


//lighting.c
t_tuple		reflect(t_tuple in, t_tuple normal);
t_color		lighting(t_minirt m, t_comps c, bool in_shadow, t_light_vars *lv);

//normal.c
t_tuple		normal_at(t_minirt *minirt, t_scene_obj *obj, t_tuple point);
t_tuple		normal_at_cylinder(t_scene_obj *cylinder, t_tuple point);

//colors
t_color		color(float r, float g, float b);
t_color		addition_color(t_color color1, t_color color2);
t_color		substraction_color(t_color color1, t_color color2);
t_color		multiply_color(t_color color1, t_color color2);
t_color		multiply_color_scalar(t_color col, float sca);
uint32_t	colour_unitrgb_hex(t_color c, float alpha);
void		colour_unitrgb_rgba(t_color *c);
// void		colour_rgba_unitrgb(t_color *c); //not used
void		color_convert(t_scene_obj *obj);

//rays
t_ray		create_ray(t_tuple vector, t_tuple point);
t_tuple		position_ray(t_ray ray, float t);
t_i			hit(t_xs *xs, t_scene_obj *obj_from);
t_ray		transform(t_ray r, t_matrix4 m);
t_xs		intersect_world(t_minirt *minirt, t_ray r);

//shading
t_comps		prepare_computations(t_minirt *minirt, t_i i, t_ray r);
t_color		shade_hit(t_minirt *minirt, t_comps comps, bool in_shadow);
t_color		color_at(t_minirt *minirt, t_ray ray);
bool		is_shadowed(t_minirt *minirt, t_tuple point, t_scene_obj *obj);

//camera
t_matrix4	view_transform(t_tuple from, t_tuple to, t_tuple up);
void		init_camera(t_minirt *minirt);

//intersections.c
t_xs		*intersects_sphere(t_scene_obj *obj, t_ray r, t_xs *xs);
t_xs		*intersect(t_minirt *minirt, t_scene_obj *obj, t_ray ray, t_xs *xs);
t_i			intersection(float intersection, void *obj);
void		intersections(t_xs	*xs, t_i i1, t_i i2);

//intersect_cylinder.c
t_xs		*intersects_cylinder(t_scene_obj *obj, t_ray r, t_xs *xs);
void		init_i_to_zeroes(t_i *i1, t_i *i2);

//intersect_utils.c
void	swap_t_values(float *t);

//transformation functions
t_matrix4	generate_transformation_mtrx(t_minirt *minirt, t_scene_obj *obj);
t_matrix4	cylinder_rotation(t_scene_obj *obj);
t_matrix4	plane_rotation(t_scene_obj *obj);

//utils
bool		is_equal(float a, float b);

#endif
