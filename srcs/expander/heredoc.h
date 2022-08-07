#ifndef HEREDOC_H
# define HEREDOC_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>

# define READ 0
# define WRITE 1

# include ".dev/libft.h" //has to be changed
# include ".dev/main.h" 

typedef struct s_cmd {
	pid_t		     pid; // waitpidのため
	const char	 *raw_str; // 入力それ自体
	char         **args;
	//  t_envvar     *envvar;
	int          redin_fd;  // dup2で使う
	int          redout_fd;
	int          ret_val; // 返り値
}	t_cmd;

typedef struct s_cmd_list{
	pid_t	pid; // for waitpid
//	t_cmd_list_type	type; // head, pipeline, or, and, braces
	void	*contents; // bracesなら*t_cmd_list, それ以外なら*t_cmd
	int	ret_val; // 返り値
	struct s_cmd_list *next;
} t_cmd_list;

int	ft_strcmp(const char *s1, const char *s2);

#endif
