/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/29 13:35:08 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include <unistd.h>

typedef struct s_var {
	char			*key;
	char			*value;
	int				is_exported;
	struct s_var	*next;
}	t_var;

typedef struct s_environ {
	int		exit_status;
	pid_t	parent_pid;
	t_var	*vars;
}	t_environ;

/**
 *  This function generates minishell environment used by malloc(3).
 *  This function should return non-NULL pointer.
 */
t_environ	*init_environ(void);

/**
 *  This function frees the minishell environ.
 *  This function always returns NULL.
 */
void		*destroy_environ(t_environ *env);

/**
 *  This function generates the array of environ variables,
 *  which can be passed to the 3rd argument of execve.
 */
char		**generate_envp(t_environ *env);

char		*ft_getenv(const char *name, t_environ *env);
int			ft_putenv(const char *string, t_environ *env);
int			ft_unsetenv(const char *name, t_environ *emv);

/**
 *  This function returns the string representation of the stored exit status.
 *  Returned string from this function should not be freed.
 */
const char	*get_exit_status_str(t_environ *env);

#endif /* ENVIRON_H */
