#ifndef LIGHTING_H
# define LIGHTING_H

//Material light properties
typedef struct	s_material
{
	float	ambient;
	float	diffuse;
	float	specular;
	float	ratio;
}	t_material;

//lighting.c
t_tuple	normal_at_sphere(t_minirt *m, t_sphere s, t_tuple p);
t_tuple	reflect(t_ray in_ray, t_tuple normal);

#endif