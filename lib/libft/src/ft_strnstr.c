/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:54:30 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/17 17:25:45 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//el: fixed norm error with line splitting line 31.
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;

	if (little[0] == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while ((big[i + j] == little[j]) && big[i + j] && little[j]
				&& (i + j < len))
			{
				if (little[j + 1] == '\0')
					return ((char *)&big[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
