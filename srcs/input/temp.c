//#include"../../libft/libft.h" //need to modify the path
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
*/
int	main(void)
{
	char *line;

	line = NULL;
	while ((line = readline("minishell> ")))
	{
		add_history(line);
		free(line);
	}
	free(line);
	printf("exit\n");
//	rl_clear_history;  ->I guess it's not necessary.
	return (0);
}
