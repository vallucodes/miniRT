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
	out = scalar_multiply_tuple(normal, tmp);
	out = substraction_tuples(in, out);
	return (out);
}

/**
 * @brief Returns combined shading for given light conditions and contributions.
 * @details ambient + specular + diffuse weighted depending on relative position
 * 			between light, camera and object(s)
 */
t_color	lighting(t_minirt m, t_comps c, bool in_shadow, t_light_vars *l)
{
	t_color	res;

	if (l->skip == false)
	{
		l->dif_col = multiply_color_scalar(l->eff_col, c.obj->mat.diffuse
				* l->l_dot_n);
		l->reflect_vec = reflect(negate_tuple(l->light_vec), c.normalv);
		l->r_dot_e = dot_tuple(l->reflect_vec, c.eyev);
		if (l->r_dot_e <= 0)
			l->spec_col = color(0, 0, 0);
		else
		{
			l->fac = pow(l->r_dot_e, c.obj->mat.shininess);
			l->spec_col = multiply_color_scalar(l->eff_col,
					c.obj->mat.specular * l->fac);
		}
	}
	res = addition_color(addition_color(l->amb_col, l->dif_col), l->spec_col);
	return (res);
}
