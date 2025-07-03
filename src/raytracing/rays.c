/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:08:18 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/03 19:08:19 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_ray(t_tuple vector, t_tuple point)
{
	t_ray	ray;

	ray.origin = point;
	ray.dir = vector;
	return (ray);
}

t_tuple	position_ray(t_ray ray, float t)
{
	t_tuple	new_point;

	new_point = addition_tuples(scalar_multiply_tuple(ray.dir, t), ray.origin);
	return (new_point);
}

t_ray	transform(t_ray r, t_matrix4 m)
{
	r.dir = multiply_mtrx_by_tuple(m, r.dir);
	r.origin = multiply_mtrx_by_tuple(m, r.origin);
	return (r);
}
