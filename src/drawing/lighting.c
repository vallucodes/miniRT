#include "minirt.h"

t_light	init_point_light(t_tuple pos, t_color color, float ratio)
{
	t_light	light;

	light.ori = pos;
	light.col = color;
	light.ratio = ratio;
	return (light);
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
	// printf("tmp: %f\n", tmp);

	out = scalar_multiply_tuple(normal, tmp);
	//print_tuple(out);

	out = substraction_tuples(in, out);

	return (out);
}

/**
 * @brief Returns combined shading for given light conditions and contributions
 * @details ambient + specular + diffuse weighted depending on relative position
 * 			between light, camera and object(s)
 * @param [in] m: Object material
 * @param [in] l: Light source
 * @param [in] p: Point of hit
 * @param [in] c_v: Camera vector
 * @param [in] n_v: Normal vector
 * @todo Needs to take into account the scene file's ambient value.
 */
t_color	lighting(t_material m, t_light l, t_tuple p, t_tuple c_v, t_tuple n_v, bool in_shadow)
{
	t_light_vars	lv;

	lv.eff_col = multiply_color_scalar(m.col, l.ratio);
	// printf("effective colour\n");
	// print_colour(lv.eff_col);

	lv.light_vec = normalize_tuple(substraction_tuples(l.ori, p));
	// printf("light vector\n");
	// print_tuple(lv.light_vec);

	lv.amb_col = multiply_color_scalar(lv.eff_col, m.ambient);
	// printf("ambient colour\n");
	// print_colour(lv.amb_col);

	if (in_shadow == true)
	{
		lv.dif_col = color(0, 0, 0);
		lv.spec_col = color(0, 0, 0);
	}
	else
	{
		lv.l_dot_n = dot_tuple(lv.light_vec, n_v);
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
	}
	return (addition_color(addition_color(lv.amb_col, lv.dif_col), lv.spec_col));
}
