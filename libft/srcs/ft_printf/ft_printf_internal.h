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

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include "ft_apulong.h"
# include <stdarg.h>
# include <stdint.h>

enum e_ftpf_flags {
	FTPF_MINUS	= 0x1,
	FTPF_ZERO	= 0x2,
	FTPF_DOT	= 0x4,
	FTPF_HASH	= 0x8,
	FTPF_SPACE	= 0x10,
	FTPF_PLUS	= 0x20,
	FTPF_QUOTE	= 0x40
};

enum e_ftpf_length {
	FTPF_INT		= 0,
	FTPF_CHAR		= 1,
	FTPF_SHORT		= 2,
	FTPF_LONG		= 3,
	FTPF_LLONG		= 4,
	FTPF_LDOUBLE	= 5,
	FTPF_SIZE_T		= 6,
	FTPF_INTMAX_T	= 7,
	FTPF_PTRDIFF_T	= 8
};

typedef struct s_ftpf_conv {
	int			flags;
	int			minfield;
	int			precision;
	int			length;
	int			spacepadlen;
	int			prefixlen;
	int			zeropadlen;
	int			datalen;
}	t_ftpf_conv;

typedef struct s_ftpf {
	int			fd;
	const char	*fmt;
	va_list		args;
	t_ftpf_conv	*conv;
	int			ret;
	int			errnum;
}	t_ftpf;

typedef struct s_ftpf_float {
	t_ft_apulong	ap;
	int				sign;
	long			e0;
	char			buf[800];
}	t_ftpf_float;

/* ftpf_option_bonus.c */
void	ftpf_option(t_ftpf *param);

/* ftpf_length_bonus.c */
void	ftpf_length(t_ftpf *param);

/* ftpf_type_bonus.c */
void	ftpf_type(t_ftpf *param);

/* ftpf_out_*_bonus.c */
void	ftpf_out_signed(t_ftpf *param);
void	ftpf_out_unsigned(t_ftpf *param);
void	ftpf_out_float(t_ftpf *param);
void	ftpf_out_char(t_ftpf *param);
void	ftpf_out_string(t_ftpf *param);
void	ftpf_out_hexfloat(t_ftpf *param);

/* ftpf_float_get_bonus.c */
int		ftpf_dbl_getdata(t_ftpf_float *fl, double d);
void	ftpf_dbl_other(t_ftpf_float *fl, t_ftpf *param);

/* ftpf_float_utils_bonus.c */
void	ftpf_trimdata(t_ftpf_float *fl, int e0, t_ftpf *param);
void	ftpf_out_float_f(t_ftpf_float *fl, int len, t_ftpf *param);
void	ftpf_out_float_e(t_ftpf_float *fl, int len, t_ftpf *param);

/* ftpf_write_bonus.c */
int		ftpf_write(const void *buf, size_t nbyte, t_ftpf *param);
int		ftpf_putpad(int pad, int nbyte, t_ftpf *param);
void	ftpf_putnbr(intmax_t n, int base, int cap, t_ftpf *param);
void	ftpf_putunbr(uintmax_t n, int base, int cap, t_ftpf *param);

#endif /* FT_PRINTF_INTERNAL_H */