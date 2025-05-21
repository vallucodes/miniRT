#include "../../inc/minirt.h"

static int	is_in_charset(const char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

/**
  * @brief Counts the number of words in a string, separated by chars in a set.
  * @param [in] *s: string to split. 
  * @param [in] *set: characters to split by. 
  * @return Int number of words 
  */
int	fun_words(const char *s, const char *set)
{
	int	words;

	words = 0;
	while (*s)
	{
		if (!is_in_charset(*s, set))
		{
			words++;
			while (*s && !is_in_charset(*s, set))
				s++;
		}
		else
			s++;
	}
	return (words);
}

static int	free_array(char **str, int size)
{
	while (size)
	{
		free(str[size]);
		size--;
	}
	return (0);
}

static int	fun_chopper(char **plate, const char *s, const char *set, int w)
{
	int	loc;
	int	index;
	int	str_num;

	loc = 0;
	index = 0;
	str_num = 0;
	while (str_num < w)
	{
		while (s[index] && is_in_charset(s[index], set))
			index++;
		loc = index;
		while (s[index] && !is_in_charset(s[index], set))
			index++;
		plate[str_num] = ft_substr(s, loc, index - loc);
		if (!plate[str_num])
			return (free_array(plate, str_num));
		str_num++;
	}
	plate[str_num] = NULL;
	return (1);
}

/**
  * @brief Splits a string into a matrix of strings separated by chars in a set.
  * @param [in] *s: string to split. 
  * @param [in] *set: characters to split by. 
  * @return Memory allocated NULL terminated matrix of strings. NULL on fail. 
  * @details Just a modified ft_split(). Essentially C09 from piscine. 
  */
char	**line_split_set(const char *s, const char *set)
{
	char	**words;
	int		wordcount;
	int		chopping;

	if (!s)
		return (NULL);
	wordcount = fun_words(s, set);
	words = malloc((wordcount + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	chopping = fun_chopper(words, s, set, wordcount);
	if (!chopping)
		return (NULL);
	return (words);
}
