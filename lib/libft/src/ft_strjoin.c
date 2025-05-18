/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:54:43 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/17 11:44:10 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//el: changed line 21 if() from || to &&
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*dst;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)ft_calloc(1 + len, sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, len + 1);
	return (dst);
}
