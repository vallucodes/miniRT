#include "../inc/minirt.h"

void fun_test_parsed_output(char **av, t_parse *ps);

int	main(int ac, char **av)
{
	t_parse	*ps;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./minirt <scene file>.rt\n", STDERR_FILENO);
		return (1);
	}
	ps = ft_calloc(1, sizeof(t_parse));
	file_check(av, ps);

	if (!parsing_gateway(ps))
	{
		exit (EXIT_FAILURE);
	}

	fun_test_parsed_output(av, ps);

	close(ps->fd);
	ft_lstclear(&ps->objects, &free);
	free(ps);

	return (0);
}

void fun_test_parsed_output(char **av, t_parse *ps)
{
	printf("Infile: %s\n\n", av[1]);

	printf("Printing default optical objects:\n");
	printf("\nAmbient light settings:\n");
	printf("Count: %i | Ratio: %f | RGB: %i, %i, %i", ps->amb_b, ps->amb_s.ratio, ps->amb_s.r, ps->amb_s.g, ps->amb_s.b);

	printf("\n\nDiffuse light settings:\n");
	printf("Count: %i | Ratio: %f | Pos: %f, %f, %f", ps->lig_b, ps->lig_s.ratio, ps->lig_s.cx, ps->lig_s.cy, ps->lig_s.cz);
	
	printf("\n\nCamera settings:\n");
	printf("Count: %i | FOV: %i | Pos: %f, %f, %f | Nor: %f, %f, %f\n", ps->cam_b, ps->cam_s.fov, ps->cam_s.cx, ps->cam_s.cy, ps->cam_s.cz, ps->cam_s.ox, ps->cam_s.oy, ps->cam_s.oz);
	
	printf("\nPrinting scene objects in .rt order:\n");
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
		printf("Current node height: %f\n\n", ((t_scene_obj *)temp->content)->height);
		temp = temp -> next;
		c++;
	}
}
