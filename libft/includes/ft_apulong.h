/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apulong.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:17:43 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:45:41 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_APULONG_H
# define FT_APULONG_H

# include <limits.h>

# ifndef FT_APULONG_SIZE
#  define FT_APULONG_SIZE 64
# endif /* FT_APULONG_SIZE */

typedef struct s_ft_apulong {
	unsigned long	l[FT_APULONG_SIZE];
	int				size;
}	t_ft_apulong;

t_ft_apulong	ft_apulong_add(t_ft_apulong a, t_ft_apulong b);
int				ft_apulong_cmp(t_ft_apulong a, t_ft_apulong b);
t_ft_apulong	ft_apulong_cpy(t_ft_apulong a);
t_ft_apulong	ft_apulong_div10(t_ft_apulong a, unsigned long *m);
t_ft_apulong	ft_apulong_mul(t_ft_apulong a, unsigned long b);
t_ft_apulong	ft_apulong_pow(unsigned long a, unsigned int p);
const char		*ft_apulong_str(t_ft_apulong a, char *str);
t_ft_apulong	ft_apulong_val(unsigned long val);

#endif /* FT_APULONG_H */