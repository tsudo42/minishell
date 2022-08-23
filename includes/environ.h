/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "libft.h"
# include "builtin.h"
# include "minishell.h"

# define ENV_ERRMSG "minishell"
# define ENVIRON_ERRMSG "minishell"
//# define ENV_INTERNAL_ERRMSG "environ internal error"
//# define ENV_INTERNAL_ERRNUM -1

extern char	**environ;

int envlen(void);
void	init_environ(void);
char	*ft_getenv(const char *name);
int		ft_setenv(const char *name, const char *value, int overwrite);
int		ft_putenv(const char *string);
int find_name(const char *name);
int		ft_unsetenv(const char *name);
void	free_environ(void);
int	print_env(const char *string);
char **add_environ(const char *string);

/**
 *  This function stores the argument as exit status.
 */
void		set_exit_status(int status);

/**
 *  This function returns the stored exit status.
 */
int			get_exit_status(void);

/**
 *  This function returns the string representation of the stored exit status.
 *  This function returns NULL when malloc(3) fails.
 */
const char	*get_exit_status_str(void);

#endif /* ENVIRON_H */
