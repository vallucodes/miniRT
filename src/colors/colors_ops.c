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
	new_color.g = color1.g + color2.g;
	new_color.b = color1.b + color2.b;
	return (new_color);
}

t_color	substraction_color(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r - color2.r;
	new_color.g = color1.g - color2.g;
	new_color.b = color1.b - color2.b;
	return (new_color);
}

t_color	multiply_color(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r * color2.r;
	new_color.g = color1.g * color2.g;
	new_color.b = color1.b * color2.b;
	return (new_color);
}

/**
 * @brief Return t_color, result of scalar multiplication of given t_color
 */
t_color	multiply_color_scalar(t_color colour, float scalar)
{
	t_color	new_colour;

	new_colour.r = colour.r * scalar;
	new_colour.g = colour.g * scalar;
	new_colour.b = colour.b * scalar;
	return (new_colour);
}
