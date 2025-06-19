#ifndef UTILS_H
# define UTILS_H

//utils_conversions.c
double	string_to_double(const char *str);
int		strict_atoi(const char *nptr);

//utils_matrix.c
void	free_matrix(char **matrix);

//ft_split_set.c
char	**line_split_set(const char *s, const char *set);
int		fun_words(const char *s, const char *set);

//utils_error.c
void	put_error(char *message);
bool	free_helper(t_parse *ps, char **matrix, void *tmp, char *err);

#endif
