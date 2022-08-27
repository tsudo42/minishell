/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:06:09 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "libft.h"
# include "builtin.h"
# include "minishell.h"
# include "utils.h"

int			init_environ(void);
char		*ft_getenv(const char *name);
int			ft_setenv(const char *name, const char *value, int overwrite);
int			ft_putenv(const char *string);
int			ft_unsetenv(const char *name);

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
