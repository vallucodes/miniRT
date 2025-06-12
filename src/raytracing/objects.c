#include "minirt.h"

/**
 * @brief Create and give default attributes to a sphere type t_scene_obj
 * @returns t_scene_obj type = SPHERE (1) object
 * @details some redundancy due to the difference in how the .rt files are
 * 			formatted and how the RT itself likes its values.
 */
t_scene_obj	sphere(t_minirt *minirt)
{
	t_scene_obj	s;

	s.type = SPHERE;
	s.cx = 0;
	s.cy = 0;
	s.cz = 0;
	s.ori = create_point(s.cx, s.cy, s.cz);
	s.radius = 1;
	s.mat = init_material();
	s.col = s.mat.col;
	colour_unitrgb_rgba(&s.col);
	s.col.hex = colour_unitrgb_hex(s.col, 1);
	s.r = s.col.r;
	s.g = s.col.g;
	s.b = s.col.b;
	s.transform = identity();
	return (s);
}
