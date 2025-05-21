#include "../../inc/minirt.h"

/**
 * @brief On list addition failure, print error and free incomplete list.  
 * @param [in] **list: t_list
 * @return Always false. To be used in return() of calling function. 
 */
static bool	parse_list_error(t_list **list)
{
	put_error(ERR_SCENELST);
	ft_lstclear(list, &free);
	return (false);
}

/**
 * @brief Adds the passed scene object to a linked list of objects. 
 * @param [in] *tmp: the object to be added. 
 * @param [in] ps: t_parse 
 * @return True on successful addition
 * @details Memory is allocated by list functions. 
 */
bool	parse_add_obj_list(t_scene_obj *tmp, t_parse *ps)
{
	t_list	*new_node;

	new_node = ft_lstnew(tmp);
	if (new_node == NULL)
	{
		free(tmp);
		return (parse_list_error(&ps->objects));
	}
	ft_lstadd_back(&ps->objects, new_node);
	return (true);
}
