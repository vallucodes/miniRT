#include "minirt.h"

float **view_transform(t_minirt *minirt, t_tuple from, t_tuple to, t_tuple up)
{
	float	**t;
	t_tuple	forward;
	t_tuple	left;
	t_tuple	true_up;


	forward = normalize_tuple(substraction_tuples(to, from));
	left = cross_tuple(forward, normalize_tuple(up));
	true_up = cross_tuple(left, forward);

	t = matrix_alloc(minirt, 4);
	matrix_fill_zero(t, 4);
	t[0][0] = left.x;
	t[0][1] = left.y;
	t[0][2] = left.z;
	t[1][0] = true_up.x;
	t[1][1] = true_up.y;
	t[1][2] = true_up.z;
	t[2][0] = -forward.x;
	t[2][1] = -forward.y;
	t[2][2] = -forward.z;
	t[3][3] = 1;
	t = multiply_mtrx_by_mtrx(minirt, t, translation(minirt, -from.x, -from.y, -from.z), 4);
	return(t);
}

void	camera(t_minirt *minirt)
{
	t_camera	*c;
	float		half_view;
	float		aspect_ratio;

	c = &minirt->world->cam_s;
	c->fov_r = c->fov * (M_PI / 180.0f);
	half_view = tan(c->fov_r / 2);
	aspect_ratio = (float)c->hsize / (float)c->vsize;
	if (aspect_ratio >=1)
	{
		c->half_width = half_view;
		c->half_height = half_view / aspect_ratio;
	}
	else
	{
		c->half_width = half_view * aspect_ratio;
		c->half_height = half_view;
	}
	minirt->world->cam_s.pixel_size = (c->half_width * 2) / c->hsize;
	minirt->world->cam_s.transform = identity(minirt);
}

t_ray	ray_for_pixel(t_minirt *minirt, t_camera *c, int px, int py)
{
	float	xoffset;
	float	yoffset;
	float	world_x;
	float	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	xoffset = (px + 0.5) * c->pixel_size;
	yoffset = (py + 0.5) * c->pixel_size;

	// printf("xoffset %f\n", xoffset);
	// printf("yoffset %f\n", yoffset);

	world_x = c->half_width - xoffset;
	world_y = c->half_height - yoffset;

	// printf("world_x %f\n", world_x);
	// printf("world_y %f\n", world_y);

	pixel = multiply_mtrx_by_tuple(inverse_matrix(minirt, c->transform, 4), create_point(world_x, world_y, -1), 4);
	// print_tuple(pixel);
	origin = multiply_mtrx_by_tuple(inverse_matrix(minirt, c->transform, 4), create_point(0, 0, 0), 4);
	// print_tuple(origin);
	direction = normalize_tuple(substraction_tuples(pixel, origin));
	// print_tuple(direction);
	return (create_ray(direction, origin));
}
