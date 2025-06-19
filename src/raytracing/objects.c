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
 * @brief Create and give default attributes to a plane type t_scene_obj
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
	p.transform = identity();
	return (p);
}

/**
 * @brief Create and give default attributes to a cylinder type t_scene_obj
 * @returns t_scene_obj: type = CYLINDER (2)
 */
t_scene_obj	cylinder(void)
{
	t_scene_obj	c;

	c.type = CYLINDER;
	c.cx = 0;
	c.cy = 0;
	c.cz = 0;
	c.ori = create_point(c.cx, c.cy, c.cz);
	c.ox = 0;
	c.oy = 0;
	c.oz = 0;
	c.nor = create_point(c.ox, c.oy, c.oz);
	c.radius = 1;
	c.height = 10000;
	c.max = c.height / 2;
	c.min = -c.max;
	c.mat = init_material();
	c.col = c.mat.col;
	colour_unitrgb_rgba(&c.col);
	c.col.hex = colour_unitrgb_hex(c.col, 1);
	c.r = c.col.r;
	c.g = c.col.g;
	c.b = c.col.b;
	c.transform = identity();
	return (c);
}
