#ifndef PARSING_H
# define PARSING_H

typedef struct s_parse
{
	int	fd;
}	t_parse;

//file_operations.c
int		file_check(char **av, t_parse ps);

//parsing.c
bool	parsing_gateway(int ac, char **av);

#endif