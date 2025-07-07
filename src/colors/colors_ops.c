/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:49:44 by elehtone          #+#    #+#             */
/*   Updated: 2025/07/07 15:08:43 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color(float r, float g, float b)
{
	t_color	new_color;

	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	return (new_color);
}

t_color	addition_color(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r + color2.r;
	if (new_color.r > 255)
		new_color.r = 255;
	new_color.g = color1.g + color2.g;
	if (new_color.g > 255)
		new_color.g = 255;
	new_color.b = color1.b + color2.b;
	if (new_color.b > 255)
		new_color.b = 255;
	return (new_color);
}

t_color	substraction_color(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r - color2.r;
	if (new_color.r < 0)
		new_color.r = 0;
	new_color.g = color1.g - color2.g;
	if (new_color.g < 0)
		new_color.g = 0;
	new_color.b = color1.b - color2.b;
	if (new_color.b < 0)
		new_color.b = 0;
	return (new_color);
}

t_color	multiply_color(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r * color2.r;
	if (new_color.r > 255)
		new_color.r = 255;
	new_color.g = color1.g * color2.g;
	if (new_color.g > 255)
		new_color.g = 255;
	new_color.b = color1.b * color2.b;
	if (new_color.b > 255)
		new_color.b = 255;
	return (new_color);
}

/**
 * @brief Return t_color, result of scalar multiplication of given t_color
 */
t_color	multiply_color_scalar(t_color color, float scalar)
{
	t_color	new_color;

	new_color.r = color.r * scalar;
	if (new_color.r > 255)
		new_color.r = 255;
	new_color.g = color.g * scalar;
	if (new_color.g > 255)
		new_color.g = 255;
	new_color.b = color.b * scalar;
	if (new_color.b > 255)
		new_color.b = 255;
	return (new_color);
}
