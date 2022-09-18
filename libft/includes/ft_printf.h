/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:50:15 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:51:38 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <errno.h>
# include <stddef.h>

int		ft_dprintf(int fd, const char *fmt, ...);
int		ft_printf(const char *fmt, ...);
int		ft_printf_bonus(const char *fmt, ...);

#endif /* FT_PRINTF_H */