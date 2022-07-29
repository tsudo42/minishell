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

# include "builtin.h"

extern char	**environ;

int		ft_init_environ(void);
char	*ft_getenv(const char *name);
int		ft_setenv(const char *name, const char *value, int overwrite);
int		ft_putenv(const char *string);
int		ft_unsetenv(const char *name);

#endif /* ENVIRON_H */
