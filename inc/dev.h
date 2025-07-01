#ifndef DEV_H
# define DEV_H

# include "raytracing.h"

//print utils
void	print_ray(t_ray r);
void	print_xs(t_xs *xs);
void	print_matrix(t_matrix4 m, char *msg, int size);
void	print_tuple(t_tuple t);
void	print_colour(t_color c);
void	print_comps(t_comps *comps);
void	print_camera(t_camera *cam);
void	fun_test_parsed_output(char **av, t_parse *ps);

//dev
float	**create_matrix(size_t size, int flag);
void	unit_tests_3x3(void);
void	unit_tests_4x4(void);
void	unit_tests_transform_matrices(void);
void	test_normal_at_sphere(t_minirt *m);
void	test_reflect(t_minirt m);
void	test_reflect_extra(t_minirt m);
void	test_point_light_material(void);
void	test_point_light_reflections(void);
void	test_prepare_computations_outside(t_minirt *minirt, char **av);
void	test_prepare_computations_inside(t_minirt *minirt, char **av);
void	test_shading_an_intersection(t_minirt *minirt, char **av);
void	test_shading_an_intersection_from_inside(t_minirt *minirt, char **av);
void	test_ray_misses_obj(t_minirt *minirt);
void	test_ray_hits_obj(t_minirt *minirt);
void	test_intersection_behind_ray(t_minirt *minirt);
void	test_orientation(void);
void	test_camera(t_minirt *minirt);
void	test_ray_for_pixel(t_minirt *minirt);
void	test_intersect_two_spheres(t_minirt *minirt);
void	print_colour(t_color c);
void	test_shape(t_minirt *minirt);
void	test_intersect_generic(void);
void	test_plane_normal(t_minirt *minirt);
void	test_plane_intersect(t_minirt *minirt);
void	test_render_world(t_minirt *minirt);
void	test_cylinder_rotation(void);
void	test_cylinder(t_minirt *minirt);
void	test_cylinder2(t_minirt *minirt);

#endif
