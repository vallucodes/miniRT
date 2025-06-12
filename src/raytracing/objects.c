#include "minirt.h"

/**
 * @brief Create and give default attributes to a sphere type t_scene_obj 
 * @returns t_scene_obj: type = SPHERE (1) 
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

/**
 * @brief Create and give default attributes to a sphere type t_scene_obj
 * @returns t_scene_obj: type = PLANE (0)
 */
t_scene_obj	plane(t_minirt *minirt)
{
	t_scene_obj	p;

	p.type = PLANE;
	p.cx = 0;
	p.cy = 0;
	p.cz = 0;
	p.ori = create_point(p.cx, p.cy, p.cz);
	p.ox = 0;
	p.oy = 0;
	p.oz = 0;
	p.nor = create_point(p.ox, p.oy, p.oz);
	p.mat = init_material();
	p.col = p.mat.col;
	colour_unitrgb_rgba(&p.col);
	p.col.hex = colour_unitrgb_hex(p.col, 1);
	p.r = p.col.r;
	p.g = p.col.g;
	p.b = p.col.b;
	p.transform = identity(minirt);
	return (p);
}
