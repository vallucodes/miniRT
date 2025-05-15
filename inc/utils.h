#ifndef UTILS_H
# define UTILS_H

//utils_conversions.c
bool	string_to_double(char *str, double *num);

//utils_matrix.c
void	free_void(void *ptr);
void	free_matrix(char **matrix);

//ft_split_set.c
char	**line_split_set(const char *s, const char *set);

#endif