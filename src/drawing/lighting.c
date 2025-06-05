#include "minirt.h"

/**
 * @brief Find the normal vector at the given location of the given sphere
 * @returns Normal vector
 * @details Sphere needs to be in object space if its origin not at world origin
 * 			Normal calculation needs to be done in object space
 * 			Result needs to be converted to world space, normalised 
 */
t_tuple	normal_at_sphere(t_minirt *m, t_sphere s, t_tuple p)
{
	t_tuple	res;
	float **inv_transform;

	//Find point in object space
	inv_transform = inverse_matrix(m, s.transform, 4);
	//print_matrix(inv_transform, "s1 inverted transform ", 4);
	res = multiply_mtrx_by_tuple(inv_transform, p, 4);
	//printf("object_point\n");
	//print_tuple(res);

	//Find normal vector while in object space
	res = substraction_tuples(res, create_point(0, 0, 0));
	//printf("object_normal\n");
	//print_tuple(res);

	//Convert object space to world space, set w to 0 and return normalised 
	res = multiply_mtrx_by_tuple(transpose_matrix(m, inv_transform, 4), res, 4);
	res.w = 0;
	return (normalize_tuple(res));
}

/**
 * @brief Returns vector, result of reflecting vector [in] about vector [normal]
 * @todo Maybe work with rays rather than vector tuples? 
 */
t_tuple	reflect(t_tuple in, t_tuple normal)
{
	t_tuple	out;
	float	tmp;
	
	tmp = 2 * dot_tuple(in, normal);
	//printf("tmp: %f\n", tmp);

	out = scalar_multiply_tuple(normal, tmp);
	//print_tuple(out);

	out = substraction_tuples(in, out);

	return (out);
}

/**
 * @brief Returns combined shading for given light conditions and contributions 
 * @details ambient + specular + diffuse weighted depending on relative position
 * 			between light, camera and object(s)
 * @todo Needs to take into account the scene file's ambient value. 
 */
t_color	lighting(t_material m, t_light l, t_tuple p, t_tuple c_v, t_tuple n_v)
{
	t_color	effective_col;
	t_color	ambient_col;
	t_color	diffuse_col;
	t_color	specular_col;
	t_tuple	light_vec;
	t_tuple	reflect_vec;
	float	l_dot_n;
	float	r_dot_c;
	float	fac;

	printf("material colour\n");
	print_colour(m.col);
	printf("light ratio: %f, origin:\n", l.ratio);
	print_tuple(l.ori);
	printf("position\n");
	print_tuple(p);
	printf("eye/camera vec\n");
	print_tuple(c_v);
	printf("normal vec\n");
	print_tuple(n_v);
	
	effective_col = multiply_color_scalar(m.col, l.ratio);
	//printf("effective colour\n");
	//print_colour(effective_col);

	light_vec = normalize_tuple(substraction_tuples(l.ori, p));
	//printf("light vector\n");
	//print_tuple(light_vec);
	
	ambient_col = multiply_color_scalar(effective_col, m.ambient);
	//printf("ambient colour\n");
	//print_colour(ambient_col);
	
	l_dot_n = dot_tuple(light_vec, n_v);
	printf("light dot normal: %f\n", l_dot_n);

	if (l_dot_n < 0)
	{
		diffuse_col = color(0, 0, 0);
		specular_col = color(0, 0, 0);
	}
	else
	{
		diffuse_col = multiply_color_scalar(effective_col, m.diffuse * l_dot_n);
		reflect_vec = reflect(negate_tuple(light_vec), n_v);
		r_dot_c = dot_tuple(reflect_vec, c_v);
		if (r_dot_c <= 0)
			specular_col = color(0, 0, 0);
		else
		{
			fac = pow(r_dot_c, m.shininess);
			specular_col = multiply_color_scalar(effective_col, m.specular * fac * l.ratio);
		}
	}
	return (addition_color(addition_color(ambient_col, diffuse_col), specular_col));
}
