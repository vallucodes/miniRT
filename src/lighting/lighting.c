/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:52:50 by elehtone          #+#    #+#             */
/*   Updated: 2025/07/04 15:55:30 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
t_color	lighting(t_comps c, t_light_vars *l)
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
