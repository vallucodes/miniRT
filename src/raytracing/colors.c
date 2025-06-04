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

t_color	multiply_color(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r * color2.r;
	new_color.g = color1.g * color2.g;
	new_color.b = color1.b * color2.b;
	return(new_color);
}

/**
 * @brief Return t_color, result of scalar multiplication of given t_color
 */
t_color	multiply_color_scalar(t_color col, float sca)
{
	t_color	new_color;

	new_color.r = col.r * sca;
	new_color.g = col.g * sca;
	new_color.b = col.b * sca;
	return(new_color);
}

/**
 * @brief Returns a 32 bit integer containing MLX colour value. Converts from
 * 		  [0,1] ranged RT colour values. 
 * @param [in] colour: a valid RT t_color type
 * @param [in] alpha: a valid 8 bit alpha value
 * @todo will need refinement when we get further along 
 */
uint32_t	colour_conversion(t_color colour, uint8_t alpha)
{
	uint8_t	tmp_col[3];

	tmp_col[0] = colour.r * 255;
	tmp_col[1] = colour.g * 255;
	tmp_col[2] = colour.b * 255;

	return (tmp_col[0] << 24 | tmp_col[1] << 16 | tmp_col[2] << 8 | alpha);
}
