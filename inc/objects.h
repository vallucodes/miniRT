#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_sphere
{
	t_tuple		center;
	float		radius;
	float		**transform;
	t_material	mat;
}	t_sphere;

//objects.c
t_sphere	sphere(t_minirt *minirt);

#endif