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
//# include "../libft/includes/ft_string.h"
//char	*ft_strdup(const char *s1);
//char			*ft_itoa(int n);

//extern char	**environ;

# define ENV_ERRMSG "minishell"
# define ENV_INTERNAL_ERRMSG "environ internal error"
# define ENV_INTERNAL_ERRNUM -1

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

#endif /* ENVIRON_H */
