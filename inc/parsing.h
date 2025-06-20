#ifndef PARSING_H
# define PARSING_H

/**
 * @brief Min and max values for RGB, FOV, orientation, coordinate.
 */
typedef enum e_limit_vals
{
	RGB_MIN = 0,
	RGB_MAX = 255,
	FOV_MIN = 0,
	FOV_MAX = 180,
	OR_MIN	= -1,
	OR_MAX	= 1,
	CO_MIN	= -10000,
	CO_MAX	= 10000
}	t_limit_vals;

/**
 * @brief Scene object types: Plane: 0, Sphere: 1, Cylinder: 2
 */
typedef enum e_obj_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_obj_type;

/**
 * @brief Error definitions.
 */
# define ERR_GEN "Parsing error, check scene file."
# define ERR_SCENELST "Building scene list failed."
# define ERR_OPTICAL "Invalid optical object designation in scene file."
# define ERR_SCENE "Invalid scene object designation in scene file."
# define ERR_AMB "Incorrect ambient light designation."
# define ERR_DIFF "Incorrect diffuse light designation."
# define ERR_CAM "Incorrect camera designation."
# define ERR_PLANE "Incorrect plane object designation."
# define ERR_SPHERE "Incorrect sphere object designation."
# define ERR_CYL "Incorrect cylinder object designation."
# define ERR_RGB "Incorrect RGB value given in scene file."
# define ERR_CO "Incorrect coordinate value given in scene file."
# define ERR_OO "Incorrect orientation value given in scene file."
# define ERR_GEO "Incorrect geometry value given in scene file."
# define ERR_FOV "Incorrect field-of-view value given in scene file."
# define ERR_RAT "Incorrect ratio value given in scene file."

/**
 * @brief Ambient optical object.
 * @note ratio[0.0,1.0] r,g,b[0,255].
*/
typedef struct s_ambient
{
	float			ratio;
	int				r;
	int				g;
	int				b;
	t_color			col;
}	t_ambient;

/**
 * @brief Camera optical object.
 * @note cx,cy,cz[CO_MIN,CO_MAX] ox,oy,oz[OR_MIN,OR_MAX] fov[0,180]
*/
typedef struct s_camera
{
	float			cx;
	float			cy;
	float			cz;
	float			ox;
	float			oy;
	float			oz;
	int				hsize;
	int				vsize;
	float			half_width;
	float			half_height;
	float			pixel_size;
	unsigned char	fov;
	float			fov_r;
	t_tuple			ori;
	t_tuple			nor;
	t_matrix4		transform;
}	t_camera;

/**
 * @brief Light optical object.
 * @note cx,cy,cz[CO_MIN,CO_MAX] ratio[0.0,1.0] r,g,b[0,255]
*/
typedef struct s_light
{
	float			cx;
	float			cy;
	float			cz;
	float			ratio;
	int				r;
	int				g;
	int				b;
	t_tuple			ori;
	t_color			col;
}	t_light;

/**
 * @brief Struct for scene objects.
 * @note Plane (0): cx,cy,cz[CO_MIN,CO_MAX] ox,oy,oz[OR_MIN,OR_MAX] r,g,b[0,255]
 * @note Sphere (1): cx,cy,cz[CO_MIN,CO_MAX] dia r,g,b[0,255]
 * @note Cylinder (2): cx,cy,cz ox,oy,oz dia height r,g,b
 * @details We will always use truncated closed cylinders. 
 */
typedef struct s_scene_obj
{
	t_obj_type		type;
	size_t			id;
	float			cx;
	float			cy;
	float			cz;
	float			ox;
	float			oy;
	float			oz;
	int				r;
	int				g;
	int				b;
	float			dia;
	float			radius;
	float			height;
	float			min;
	float			max;
	bool			closed;
	t_tuple			ori;
	t_tuple			nor;
	t_color			col;
	t_material		mat;
	t_matrix4		transform;
	t_ray			saved_ray;
}	t_scene_obj;

/**
 * @brief Struct handling all elements related to parsing the scene.
 * @note obj_count: only scene objects. xxx_b: count of optical objects.
 * @note xxx_s: data struct for optical objects.
 * @note *objects: single linked list, all scene objects (obj_count - 1 entries)
 */
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
bool	parse_check_rgb(char *str, int *R, int *G, int *B);
bool	parse_check_coords(char *str, float *cx, float *cy, float *cz);
bool	parse_check_orient(char *str, float *ox, float *oy, float *oz);
bool	parse_check_fov(char *str, unsigned char *num);

//parse_check_attributes_2.c
bool	parse_check_geometry(char *str, float *num);

//parse_obj_list.c
bool	parse_add_obj_list(t_scene_obj *tmp, t_parse *ps);

//parse_utils.c
void	parse_fill_colour(t_color *col, int r, int g, int b);
void	parse_fill_origin(t_tuple *origin, float cx, float cy, float cz);
void	parse_fill_norm(t_tuple *norm, float ox, float oy, float oz);
void	parse_fill_size(t_camera *camera);

#endif
