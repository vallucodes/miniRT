/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:13:20 by elehtone          #+#    #+#             */
/*   Updated: 2025/01/15 19:55:23 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Different to libft strchr in that it outputs an int and adds 1 to the count.
//Oh and it only searches for '\n'.
int	fun_findnl(const char *s)
{
	int	count;
	int	slen;

	if (!s)
		return (0);
	count = 0;
	slen = ft_strlen(s);
	while (count <= slen)
	{
		if (s[count] == '\n')
			return (count + 1);
		count++;
	}
	return (0);
}
