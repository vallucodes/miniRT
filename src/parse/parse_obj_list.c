#include "../../inc/minirt.h"

/**
 * @brief Adds the passed object to a linked list of objects. 
 * @param [in] *tmp: the object to be added. 
 * @param [in] ps: t_parse, parsing struct. 
 */
void	parse_add_obj_list(void *tmp, t_parse *ps)
{
	t_list	*new_node;

	new_node = ft_lstnew(tmp);
	ft_lstadd_back(&ps->objects, new_node);
}
