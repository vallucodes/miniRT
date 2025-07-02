#include "minirt.h"

t_matrix4	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_matrix4	t;
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;

	forward = normalize_tuple(substraction_tuples(to, from));
	left = cross_tuple(forward, normalize_tuple(up));
	true_up = cross_tuple(left, forward);
	matrix_fill_zero(&t);
	t.m[0][0] = left.x;
	t.m[0][1] = left.y;
	t.m[0][2] = left.z;
	t.m[1][0] = true_up.x;
	t.m[1][1] = true_up.y;
	t.m[1][2] = true_up.z;
	t.m[2][0] = -forward.x;
	t.m[2][1] = -forward.y;
	t.m[2][2] = -forward.z;
	t.m[3][3] = 1;
	t = multiply_mtrx_by_mtrx(t, translation(-from.x, -from.y, -from.z));
	return (t);
}

static void	set_camera_vars(t_minirt *minirt)
{
	t_camera	*c;
	float		half_view;
	float		aspect_ratio;

	c = &minirt->world->cam_s;
	if (c->fov == 180)
		c->fov = 179.9; // 179.9 would be probably better, still issue: unsigned char	fov;
	c->fov_r = c->fov * (M_PI / 180.0f);
	half_view = tan(c->fov_r / 2);
	aspect_ratio = (float)c->hsize / (float)c->vsize;
	if (aspect_ratio >= 1)
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
}

void	set_camera_tranformation_matrix(t_minirt *minirt)
{
	t_tuple	from;
	t_tuple	to;
	t_tuple	orientation;
	t_tuple	up;

	from = create_point(minirt->world->cam_s.cx, minirt->world->cam_s.cy,
			minirt->world->cam_s.cz);
	orientation = create_vector(minirt->world->cam_s.ox,
			minirt->world->cam_s.oy, minirt->world->cam_s.oz);
	to = addition_tuples(from, orientation);
	if (minirt->world->cam_s.ox == 0 && minirt->world->cam_s.oz == 0)
		up = create_vector(0, 0, -1);
	else
		up = create_vector(0, 1, 0);
	minirt->world->cam_s.transform = view_transform(from, to, up);
}

void	init_camera(t_minirt *minirt)
{
	set_camera_vars(minirt);
	set_camera_tranformation_matrix(minirt);
}
