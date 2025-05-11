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
	return(new_color);
}

t_color substraction_color(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r - color2.r;
	new_color.g = color1.g - color2.g;
	new_color.b = color1.b - color2.b;
	return(new_color);
}
