/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:08:25 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/03 21:48:14 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief	Return the desired colour at current location.
 * @details	Doing some precalculations for the lighting() function for norm.
 */
t_color	shade_hit(t_minirt *m, t_comps c, bool in_shadow)
{
	t_light_vars	lv;
	t_color			res_color;

	lv.com = multiply_color_scalar(m->world->amb_s.col, m->world->amb_s.ratio);
	lv.com = multiply_color(c.obj->mat.col, lv.com);
	lv.eff_col = multiply_color_scalar(lv.com, m->world->lig_s.ratio);
	lv.amb_col = multiply_color_scalar(lv.com, c.obj->mat.ambient);
	lv.light_vec = normalize_tuple(substraction_tuples(m->world->lig_s.ori,
				c.over_point));
	lv.l_dot_n = dot_tuple(lv.light_vec, c.normalv);
	lv.skip = false;
	if (in_shadow == true || lv.l_dot_n < 0)
	{
		lv.dif_col = color(0, 0, 0);
		lv.spec_col = color(0, 0, 0);
		lv.skip = true;
	}
	res_color = lighting(*m, c, in_shadow, &lv);
	return (res_color);
}

t_color	color_at(t_minirt *minirt, t_ray r)
{
	t_xs	xs;
	t_i		hit_p;
	t_comps	comps;
	bool	in_shadow;
	t_color	color_var;

	xs = intersect_world(minirt, r);
	hit_p = hit(&xs, NULL);
	if (hit_p.object == NULL)
		return (color(0, 0, 0));
	comps = prepare_computations(minirt, hit_p, r);
	in_shadow = is_shadowed(minirt, comps.over_point, hit_p.object);
	color_var = shade_hit(minirt, comps, in_shadow);
	return (color_var);
}
