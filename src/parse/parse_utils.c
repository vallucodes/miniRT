/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:55:26 by elehtone          #+#    #+#             */
/*   Updated: 2025/07/04 15:11:22 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Fills pointed t_color with unitRGB [0,1] values
 * @param [in] r,g,b: individual [0,255] RGB values
 */
void	parse_fill_colour(t_color *col, int r, int g, int b)
{
	col->r = (float)r / 255;
	col->g = (float)g / 255;
	col->b = (float)b / 255;
}

/**
 * @brief Fills pointed t_tuple (origin, point) with coordinate values
 * @param [in] cx,cy,cz: individual coordinate values
 */
void	parse_fill_origin(t_tuple *origin, float cx, float cy, float cz)
{
	origin->x = cx;
	origin->y = cy;
	origin->z = cz;
	origin->w = 1;
}

/**
 * @brief Fills pointed t_tuple (orientation, vector) with [0,1] values
 * @param [in] ox,oy,oz: individual [0,1] orientation values
 */
void	parse_fill_norm(t_tuple *norm, float ox, float oy, float oz)
{
	norm->x = ox;
	norm->y = oy;
	norm->z = oz;
	norm->w = 0;
}

void	parse_fill_size(t_camera *camera)
{
	camera->hsize = WIDTH;
	camera->vsize = HEIGHT;
}

/**
 * @brief Checks if given orientation values make a unit vector. 
 */
bool	parse_check_ori_norm(float *ox, float *oy, float *oz)
{
	float	res;

	res = fabs((*ox * *ox) + (*oy * *oy) + (*oz * *oz));
	res = fabs(sqrt(res - 1));
	if (res > EPS_ORIENT)
		return (true);
	else
		return (false);
}
