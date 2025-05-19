#ifndef PARSING_H
# define PARSING_H

//Shortened typedef to satisfy norm
typedef unsigned char	t_rgb;

//Min and max RGB and FOV values.
typedef enum e_limit_vals
{
	RGB_MIN = 0,
	RGB_MAX = 255,
	FOV_MIN = 0,
	FOV_MAX = 180
}	t_limit_vals;

//Types: Plane: 0, Sphere: 1, Cylinder: 2
typedef enum e_obj_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_obj_type;

//Structs for optical objects. 
typedef struct s_ambient
{
	float			ratio;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_ambient;

typedef struct s_camera
{
	float			cx;
	float			cy;
	float			cz;
	float			ox;
	float			oy;
	float			oz;
	unsigned char	fov;
}	t_camera;

typedef struct s_light
{
	float			cx;
	float			cy;
	float			cz;
	float			ratio;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_light;

/**
 * @brief Struct for scene objects.
 * @note Plane (0): cx,cy,cz ox,oy,oz RGB
 * @note Sphere (1): cx,cy,cz dia RGB
 * @note Cylinder (2): cx,cy,cz ox,oy,oz dia height RGB
 */
typedef struct s_scene_obj
{
	t_obj_type		type;
	float			cx;
	float			cy;
	float			cz;
	float			ox;
	float			oy;
	float			oz;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	float			dia;
	float			height;
}	t_scene_obj;

//Struct handling all elementes related to parsing. 
typedef struct s_parse
{
	int				fd;
	int				obj_count;
	unsigned char	amb_b;
	unsigned char	lig_b;
	unsigned char	cam_b;
	t_ambient		amb_s;
	t_light			lig_s;
	t_camera		cam_s;
	t_list			*objects;
}	t_parse;

//file_operations.c
int		file_check(char **av, t_parse *ps);

//parsing.c
bool	parsing_gateway(t_parse *ps);

//parse_obj_type.c
bool	parse_optical_object(char *line, t_parse *ps);
bool	parse_scene_object(char *line, t_parse *ps);

//parse_check_opt_obj.c
bool	parse_check_amb(char *line, t_parse *ps);
bool	parse_check_cam(char *line, t_parse *ps);
bool	parse_check_light(char *line, t_parse *ps);

//parse_check_scene_obj.c
bool	parse_check_sphere(char *line, t_parse *ps);
bool	parse_check_plane(char *line, t_parse *ps);
bool	parse_check_cylinder(char *line, t_parse *ps);

//parse_check_attributes_1.c
bool	parse_check_ratio(char *str, float *num);
bool	parse_check_rgb(char *str, t_rgb *R, t_rgb *G, t_rgb *B);
bool	parse_check_coords(char *str, float *cx, float *cy, float *cz);
bool	parse_check_orient(char *str, float *ox, float *oy, float *oz);
bool	parse_check_fov(char *str, unsigned char *num);

//parse_check_attributes_2.c
bool	parse_check_geometry(char *str, float *num);

//parse_obj_list.c
void	parse_add_obj_list(void *tmp, t_parse *ps);

#endif