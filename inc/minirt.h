/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:13:07 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/04 16:38:58 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <assert.h>

//System includes.
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

//42 specific includes.
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"

//Project includes.
# include "typedefs.h"
# include "linear_algebra.h"
# include "utils.h"
# include "parsing.h"
# include "raytracing.h"

//Constant defines
/**
 * @todo  M_PI Only here to stop vscode annoyance.
 */
# define M_PI			3.14159265358979323846
# define EPSILON		0.0001
# define EPS_ORIENT		0.1
# define WIDTH			400
# define HEIGHT			400
# define MALLOC			"Memory allocation failed"
# define PARSING		"Exit, parsing failure."
# define SHAPE			"Unreachable code: shape unrecognized."
# define INVERSE_MATRIX	"Matrix not invertible."

//Material default values
# define DIF_DEFAULT 0.9
# define SPEC_DEFAULT 0.9
# define SHINE_DEFAULT 200

//Attributes for viewport
typedef struct s_vp
{
	float	fov;
	float	aspect_ratio;
	float	vp_h;
	float	vp_w;
}	t_vp;

typedef struct s_minirt
{
	t_parse		*world;
	t_vp		*vp;
	mlx_image_t	*img;
	mlx_t		*mlx;
}		t_minirt;

//drawing
t_ray		ray_for_pixel(t_minirt *minirt, t_camera *c, int px, int py);
void		set_pixel_color(t_minirt *minirt);
void		render_world(t_minirt *minirt);
void		ft_keyhook(void *param);

//init.c
void		init_minirt(t_minirt *minirt);
t_material	init_material(float amb_col);
void		init_xs(t_xs *xs);
void		init_objects(t_minirt *minirt);

//error & cleanup
void		exit_error(t_minirt *minirt, const char *msg);
void		cleanup(t_minirt *minirt);

#endif
