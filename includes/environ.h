/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/12 08:08:19 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include <unistd.h>

# define ENVIRON_ERRMSG "minishell"

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
 *
 *  This function exits with 1 when malloc(3) fails.
 */
t_environ	*environ_init(void);

/**
 *  This function frees the minishell environ.
 *  This function always returns NULL.
 */
void		*environ_destroy(t_environ *env);

/**
 *  This function checks format of key, and returns 0 when the format does
 *  not contain any problem.
 *
 *  Errno will be set to EINVAL and returns -1 if key is one of following:
 *  - key is NULL.
 *  - key is an empty string.
 *  - key conatains character '='.
 */
int			variable_check_key_format(const char *key);

/**
 *  This function gets string of variable selected by key if found.
 *  Otherwise, NULL is returned.
 *
 *  The returned value of variable should not be modified or freed.
 *
 *  Argument key is checked via variable_check_key_format().
 */
char		*variable_get(const char *key, t_environ *env);

/**
 *  This function sets key-value variable.
 *
 *  If value argument is NULL, value of variable will not be updated
 *  but whether the variable is exported can be updated.
 *
 *  Environment variables are stored when export is true.
 *  Internal variables are stored when export is false.
 *
 *  When updating an internal variable with is_exp == true,
 *  the variable will be environment variable.
 *  Environment variable can be updated with is_exp == false.
 *
 *  key is checked via variable_check_key_format().
 *  This function exits with 1 when malloc(3) fails.
 */
int			variable_set( \
	const char *key, const char *value, int export, t_environ *env);

/**
 *  This function gets string of variable selected by key if found.
 *  Otherwise, NULL is returned.
 *
 *  Argument key is checked via variable_check_key_format().
 */
int			variable_unset(const char *key, t_environ *env);

/**
 *  This function creates a t_var to add key-value variable and
 *  return the t_var.
 *
 *  The key argument is checked via variable_check_key_format().
 *  This function exits with 1 when malloc(3) fails.
 *
 *  If value argument is NULL, NULL is assigned to the value of 
 *  variable.
 *
 */
t_var		*variable_add(const char *key, const char *value);

/**
 *  This function generates the array of environ variables,
 *  which can be passed to the 3rd argument of execve.
 */
char		**generate_envp(t_environ *env);

/**
 *  This function returns the string representation of the stored exit status.
 *  Returned string from this function should not be freed.
 */
const char	*get_exit_status_str(t_environ *env);

#endif /* ENVIRON_H */
