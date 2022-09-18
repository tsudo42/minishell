/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>

static int	ftdpf_write(int fildes, const void *buf, size_t nbyte, int reset)
{
	static ssize_t	nbytes_written;
	ssize_t			tmp;

	if (reset)
	{
		tmp = nbytes_written;
		nbytes_written = 0;
		return (tmp);
	}
	if (nbytes_written < 0)
		return (nbytes_written);
	tmp = write(fildes, buf, nbyte);
	if (tmp < 0)
		nbytes_written = tmp;
	else
		nbytes_written += tmp;
	return (nbytes_written);
}

static void	ftdpf_putunbr(int fd, unsigned long num, int base, int cap)
{
	const char	*numstrs;
	char		buf[32];
	size_t		i;

	numstrs = "0123456789abcdef";
	if (cap)
		numstrs = "0123456789ABCDEF";
	i = 0;
	while (num >= (unsigned int)base)
	{
		buf[31 - i] = numstrs[num % base];
		num /= base;
		i++;
	}
	buf[31 - i] = numstrs[num % base];
	ftdpf_write(fd, &(buf[31 - i]), i + 1, 0);
}

static void	ftdpf_convert_int(int fd, char convert, int i)
{
	char			c;
	unsigned int	ui;

	ui = i;
	if (convert == 'c')
	{
		if (convert == 'c')
			c = i;
		else if (convert == '%')
			c = '%';
		ftdpf_write(fd, &c, 1, 0);
	}
	else if (convert == 'd' || convert == 'i')
	{
		if (i < 0)
		{
			ftdpf_write(fd, "-", 1, 0);
			ui = -i;
		}
		ftdpf_putunbr(fd, ui, 10, 0);
	}
	else if (convert == 'u')
		ftdpf_putunbr(fd, ui, 10, 0);
	else if (convert == 'x' || convert == 'X')
		ftdpf_putunbr(fd, ui, 16, convert == 'X');
}

static void	ftdpf_convert_pointer(int fd, char convert, void *p)
{
	unsigned long	ul;

	if (convert == 's')
	{
		if (p == NULL)
			p = "(null)";
		ftdpf_write(fd, p, ft_strlen(p), 0);
	}
	else if (convert == 'p')
	{
		ul = (unsigned long)p;
		ftdpf_write(fd, "0x", 2, 0);
		ftdpf_putunbr(fd, ul, 16, 0);
	}
}

/* ************************************************************************** */
/*  This function is almost equivalent to ft_printf,                          */
/*  but output fd can be set like dprintf(3).                                 */
/*  This function can handle simple c, s, d, i, u, x, X, p conversion         */
/*  without any flags or options such as #*+0,.                               */
/*  No buffering, and no overflow checking.                                   */
/* ************************************************************************** */
int	ft_dprintf(int fd, const char *fmt, ...)
{
	va_list	ap;
	size_t	cspn;

	va_start(ap, fmt);
	while (*fmt != '\0')
	{
		if (*fmt != '%')
		{
			cspn = ft_strcspn(fmt, "%");
			ftdpf_write(fd, fmt, cspn, 0);
			fmt += cspn;
			continue ;
		}
		fmt++;
		if (*fmt == '%')
			ftdpf_write(fd, "%", 1, 0);
		else if (ft_strchr("cdiuxX", *fmt))
			ftdpf_convert_int(fd, *fmt, va_arg(ap, int));
		else if (ft_strchr("sp", *fmt))
			ftdpf_convert_pointer(fd, *fmt, va_arg(ap, void *));
		fmt++;
	}
	va_end(ap);
	return (ftdpf_write(fd, NULL, 0, 1));
}
