#ifndef PARSING_H
# define PARSING_H

//Struct handling all elementes related to parsing. 
typedef struct s_parse
{
	int	fd;
	int	obj_count;
	bool	amb_b;
	bool	diff_b;
	bool	cam_b;
	t_light	diff_s;
	t_ambient	amb_s;
	t_camera	cam_s;
	t_list	*objects;
}	t_parse;

//Structs for scene objects. 
typedef struct s_ambient
{
	float	ratio;
	unsigned char	R;
	unsigned char	G;
	unsigned char	B;
}	t_ambient;

typedef struct s_camera
{
	float	cx;
	float	cy;
	float	cz;
	float	ox;
	float	oy;
	float	oz;
	float	fov;
}	t_camera;

typedef struct s_light
{
	float	cx;
	float	cy;
	float	cz;
	float	ratio;
	unsigned char	R;
	unsigned char	G;
	unsigned char	B;
}	t_light;

typedef struct s_sphere
{
	float	cx;
	float	cy;
	float	cz;
	float	dia;
	unsigned char	R;
	unsigned char	G;
	unsigned char	B;
}	t_sphere;

typedef struct s_plane
{
	float	cx;
	float	cy;
	float	cz;
	float	nx;
	float	ny;
	float	nz;
	unsigned char	R;
	unsigned char	G;
	unsigned char	B;
}	t_plane;

typedef struct s_cylinder
{
	float	cx;
	float	cy;
	float	cz;
	float	nx;
	float	ny;
	float	nz;
	float	dia;
	float	height;
	unsigned char	R;
	unsigned char	G;
	unsigned char	B;
}	t_cylinder;

//file_operations.c
int		file_check(char **av, t_parse ps);

//parsing.c
bool	parsing_gateway(int ac, char **av);

#endif