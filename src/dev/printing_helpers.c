#include "minirt.h"

void	print_matrix(t_matrix4 m, char *msg, int size)
{
	int i = 0;
	int j = 0;
	printf("Matrix %s\n", msg);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%8.5f ", m.m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_tuple(t_tuple t)
{
	printf("print tuple\n");
	printf("t[x] = %f\n", t.x);
	printf("t[y] = %f\n", t.y);
	printf("t[z] = %f\n", t.z);
	printf("t[w] = %f\n\n", t.w);
}

void	print_colour(t_color c)
{
	printf("print color\n");
	printf("c[r] = %f\n", c.r);
	printf("c[g] = %f\n", c.g);
	printf("c[b] = %f\n\n", c.b);
}

void	print_ray(t_ray r)
{
	printf("print ray\n");
	printf("dir r[x] = %f\n", r.dir.x);
	printf("dir r[y] = %f\n", r.dir.y);
	printf("dir r[z] = %f\n", r.dir.z);
	printf("dir r[w] = %f\n", r.dir.w);
	printf("origin r[x] = %f\n", r.origin.x);
	printf("origin r[y] = %f\n", r.origin.y);
	printf("origin r[z] = %f\n", r.origin.z);
	printf("origin r[w] = %f\n\n", r.origin.w);
}
void	print_xs(t_minirt *minirt, t_xs *xs)
{
	printf("print xs\n");
	size_t i = 0;
	// int object_type;
	t_scene_obj *obj = (t_scene_obj *)xs->object;

	printf("xs.count = %zu\n", xs->count);
	while (i < xs->count)
	{
		printf("xs.t[%zu] = %f\n", i, xs->t[i]);
		// object_type = xs->object
		// printf("xs.t[%i] = %f\n\n", i, xs->t[i]);
		i++;
	}
	printf("\n");
}

void	print_comps(t_comps *comps)
{
	printf("comps: \n");
	printf("inside: %s\n", comps->inside ? "true" : "false");
	printf("obj: %p\n", (void *)comps->obj); // pointer address
	printf("point: \n");
	print_tuple(comps->point);
	printf("eyev: \n");
	print_tuple(comps->eyev);
	printf("normalv: \n");
	print_tuple(comps->normalv);
}

void	print_camera(t_camera *cam)
{
	printf("Camera struct at %p\n", (void*)cam);
	printf("hsize: %d\n", cam->hsize);
	printf("vsize: %d\n", cam->vsize);
	printf("pixel_size: %.6f\n", cam->pixel_size);
	printf("fov: %i\n", cam->fov);
	printf("fov radians: %f\n", cam->fov_r);

	printf("position: ");
	print_tuple(cam->ori);
	printf("orientation: ");
	print_tuple(cam->nor);

	printf("transform matrix of camera:\n");
	for (int i = 0; i < 4; ++i) {
		printf("  ");
		for (int j = 0; j < 4; ++j) {
			printf("%.6f ", cam->transform.m[i][j]);
		}
		printf("\n");
	}
}

void fun_test_parsed_output(char **av, t_parse *ps)
{
	printf("Infile: %s\n\n", av[1]);

	printf("Printing default optical objects:\n");
	printf("\nAmbient light settings:\n");
	printf("Count: %i | Ratio: %f | RGB: %i, %i, %i\n", ps->amb_b, ps->amb_s.ratio, ps->amb_s.r, ps->amb_s.g, ps->amb_s.b);
	printf("Ambient colour:\n");
	print_colour(ps->amb_s.col);

	printf("\nPoint light settings:\n");
	printf("Count: %i | Ratio: %f | Pos: %f, %f, %f\n", ps->lig_b, ps->lig_s.ratio, ps->lig_s.cx, ps->lig_s.cy, ps->lig_s.cz);
	printf("Point light location:\n");
	print_tuple(ps->lig_s.ori);
	printf("Point light color:\n");
	print_colour(ps->lig_s.col);

	printf("Camera settings:\n");
	printf("Count: %i | FOV: %i | Pos: %f, %f, %f | Nor: %f, %f, %f\n", ps->cam_b, ps->cam_s.fov, ps->cam_s.cx, ps->cam_s.cy, ps->cam_s.cz, ps->cam_s.ox, ps->cam_s.oy, ps->cam_s.oz);
	printf("Camera location:\n");
	print_tuple(ps->cam_s.ori);
	printf("\nCamera orientation:\n");
	print_tuple(ps->cam_s.nor);

	printf("\nPrinting scene objects in .rt order:\n");
	printf("\nPlane = 0, sphere = 1, cylinder = 2:\n");
	printf("Number of scene objects: %i\n", ps->obj_count);

	int c = 0;
	t_list	*temp = ps->objects;
	while (temp != NULL)
	{
		t_scene_obj *obj = (t_scene_obj *)temp->content;
		(void)obj;
		printf("Node: %i\n", c);
		printf("Current node address: %p\n", &temp->content);
		printf("Next node address: %p\n", temp->next);
		printf("Current node type: %i\n", ((t_scene_obj *)temp->content)->type);
		printf("Current node cx,cy,cz: %f,%f,%f\n", ((t_scene_obj *)temp->content)->cx, ((t_scene_obj *)temp->content)->cy, ((t_scene_obj *)temp->content)->cz);
		printf("Current node ox,oy,oz: %f,%f,%f\n", ((t_scene_obj *)temp->content)->ox, ((t_scene_obj *)temp->content)->oy, ((t_scene_obj *)temp->content)->oz);
		printf("Current node R,G,B: %i,%i,%i\n", ((t_scene_obj *)temp->content)->r, ((t_scene_obj *)temp->content)->g, ((t_scene_obj *)temp->content)->b);
		printf("Current node dia: %f\n", ((t_scene_obj *)temp->content)->dia);
		printf("Current node height: %f\n", ((t_scene_obj *)temp->content)->height);
		printf("Current node material diffuse: %f\n", ((t_scene_obj *)temp->content)->mat.diffuse);
		printf("Current node material specular: %f\n", ((t_scene_obj *)temp->content)->mat.specular);
		printf("Filled structs (origin, normal, colour):\n");
		print_tuple(((t_scene_obj *)temp->content)->ori);
		print_tuple(((t_scene_obj *)temp->content)->nor);
		print_colour(((t_scene_obj *)temp->content)->col);
		// print_matrix(((t_scene_obj *)temp->content)->transform, ": transformation matrix for object", 4);
		temp = temp -> next;
		c++;
	}
}
