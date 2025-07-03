/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:09:19 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/03 19:09:20 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_objects(t_minirt *minirt)
{
	int			i;
	t_list		*temp;
	t_scene_obj	*obj;

	temp = minirt->world->objects;
	i = 0;
	while (i < minirt->world->obj_count)
	{
		obj = (t_scene_obj *)temp->content;
		obj->id = i;
		if (obj->type == CYLINDER)
		{
			obj->min = -0.5;
			obj->max = 0.5;
			obj->closed = true;
		}
		obj->transform = generate_transformation_mtrx(minirt, obj);
		obj->mat = init_material(minirt->world->amb_s.ratio);
		color_convert(obj);
		temp = temp->next;
		i++;
	}
}
