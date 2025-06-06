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
t_color	lighting(t_material m, t_light l, t_tuple p, t_tuple e_v, t_tuple n_v)
{
	t_light_vars	lv;	

	printf("material colour\n");
	print_colour(m.col);
	printf("light ratio: %f, origin:\n", l.ratio);
	print_tuple(l.ori);
	printf("position\n");
	print_tuple(p);
	printf("eye/camera vec\n");
	print_tuple(e_v);
	printf("normal vec\n");
	print_tuple(n_v);
	
	lv.eff_col = multiply_color_scalar(m.col, l.ratio);
	//printf("effective colour\n");
	//print_colour(effective_col);

	lv.light_vec = normalize_tuple(substraction_tuples(l.ori, p));
	//printf("light vector\n");
	//print_tuple(light_vec);
	
	lv.amb_col = multiply_color_scalar(lv.eff_col, m.ambient);
	//printf("ambient colour\n");
	//print_colour(ambient_col);
	
	lv.l_dot_n = dot_tuple(lv.light_vec, n_v);
	printf("light dot normal: %f\n", lv.l_dot_n);

	if (lv.l_dot_n < 0)
	{
		lv.dif_col = color(0, 0, 0);
		lv.spec_col = color(0, 0, 0);
	}
	else
	{
		lv.dif_col = multiply_color_scalar(lv.eff_col, m.diffuse * lv.l_dot_n);
		lv.reflect_vec = reflect(negate_tuple(lv.light_vec), n_v);
		lv.r_dot_e = dot_tuple(lv.reflect_vec, e_v);
		if (lv.r_dot_e <= 0)
			lv.spec_col = color(0, 0, 0);
		else
		{
			lv.fac = pow(lv.r_dot_e, m.shininess);
			lv.spec_col = multiply_color_scalar(lv.eff_col, m.specular * lv.fac);
		}
	}
	return (addition_color(addition_color(lv.amb_col, lv.dif_col), lv.spec_col));
}
