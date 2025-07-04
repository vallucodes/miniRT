/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:12:21 by elehtone          #+#    #+#             */
/*   Updated: 2025/07/04 13:09:18 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//Different to libft strchr in that it outputs an int and adds 1 to the count.
//Oh and it only searches for '\n'.
static int	fun_findnl(const char *s)
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

/*
 * Read buffers to line variable.
 * Parameters: file descriptor (fd), pointer to char (**catted)
 * Return: number of read chars (int). On error -1.
 *   Checks sanity of read(), checks buffer for '\n', loops until '\n'.
 */
static int	fun_fill_string(int fd, char **catted)
{
	int		read_bytes;
	char	buffer[BUFFER_SIZE + 1];
	char	*cleaner;

	while (2 + 2 != 5)
	{
		read_bytes = fun_findnl(*catted);
		if (read_bytes != 0)
			return (read_bytes);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (-1);
		if (read_bytes == 0)
			return (ft_strlen(*catted));
		buffer[read_bytes] = '\0';
		cleaner = *catted;
		*catted = ft_strjoin(*catted, buffer);
		free(cleaner);
		if (!*catted)
			return (-1);
	}
	return (-5);
}

/*
 * Function to return the next line of a file descriptor.
 * Parameters: file descriptor (fd)
 * Return: allocated fetched line (char pointer). NULL on error.
 *   1. Checks for sanity of inputs. 2. Uses fun_fill_string() to count line
 *      length and concatenate the line (NOTE: works in whole buffers).
 *      3. Splits into line and any chars after a (\n). 4. Returns line.
 */
char	*get_next_line(int fd, bool clean)
{
	static char	*remnants;
	char		*line;
	char		*cleaner;
	int			str_len;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str_len = fun_fill_string(fd, &remnants);
	if (str_len < 0 || clean == true)
	{
		free(remnants);
		return (NULL);
	}
	line = ft_substr(remnants, 0, str_len);
	cleaner = remnants;
	remnants = ft_substr(cleaner, str_len, ft_strlen(cleaner));
	if (!line || !remnants)
	{
		free(line);
		free(cleaner);
		return (NULL);
	}
	free(cleaner);
	return (line);
}
