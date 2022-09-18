/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_out_string_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:22:49 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:48:02 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include "ft_string.h"

static void	ftpf_string_countlen(size_t len, t_ftpf *param)
{
	t_ftpf_conv	*conv;

	conv = param->conv;
	if (len >= INT_MAX)
	{
		len = INT_MAX;
		param->errnum = EOVERFLOW;
	}
	conv->datalen = len;
	if (conv->flags & FTPF_DOT)
	{
		if (conv->datalen > conv->precision)
			conv->datalen = conv->precision;
	}
	if (conv->flags & FTPF_MINUS || !(conv->flags & FTPF_ZERO))
		conv->spacepadlen = conv->minfield - conv->datalen;
	else
		conv->zeropadlen = conv->minfield - conv->datalen;
}

/* assuming UTF-8 and considering precision trimming */
static int	ftpf_wcslen_helper(const wchar_t *wcs, int maxlen)
{
	int	len;
	int	i;

	if ((*wcs & 0x80) == 0)
		len = 1;
	else if ((*wcs & 0xe0) == 0xc0)
		len = 2;
	else if ((*wcs & 0xf0) == 0xe0)
		len = 3;
	else
		len = 4;
	if (len > maxlen)
		(void)maxlen;
	i = 0;
	while (i < len)
	{
		if (*wcs == L'\0' || *wcs > 0xFF || *wcs < 0)
			return (-2);
		i++;
		wcs++;
	}
	return (len);
}

/* assuming UTF-8 and considering precision trimming */
static size_t	ftpf_wcslen(const wchar_t *wcs, t_ftpf *param)
{
	size_t	len;
	int		ret;

	len = 0;
	while (*wcs != L'\0')
	{
		if (param->conv->flags & FTPF_DOT)
			ret = ftpf_wcslen_helper(wcs, param->conv->precision - len);
		else
			ret = ftpf_wcslen_helper(wcs, 5);
		if (ret == -1)
			break ;
		else if (ret == -2)
		{
			param->errnum = EILSEQ;
			break ;
		}
		len += ret;
		wcs += ret;
	}
	if (param->errnum == EILSEQ)
		return (0);
	return (len);
}

static void	ftpf_ws(t_ftpf *param)
{
	size_t	len;
	wchar_t	*ws;

	ws = va_arg(param->args, wchar_t *);
	if (ws == NULL)
		ws = L"(null)";
	ftpf_string_countlen(ftpf_wcslen(ws, param), param);
	if (!(param->conv->flags & FTPF_MINUS))
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	ftpf_putpad('0', param->conv->zeropadlen, param);
	len = param->conv->datalen;
	while (len > 0)
	{
		ftpf_write(ws, 1, param);
		ws++;
		len--;
	}
	if (param->conv->flags & FTPF_MINUS)
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	param->fmt++;
}

void	ftpf_out_string(t_ftpf *param)
{
	void	*s;

	if (param->conv->minfield >= 2147483646)
		param->errnum = EOVERFLOW;
	if (*(param->fmt) == 'S')
		param->conv->length = FTPF_LONG;
	if (param->conv->length == FTPF_LONG || param->conv->length == FTPF_LLONG)
	{
		ftpf_ws(param);
		return ;
	}
	s = va_arg(param->args, char *);
	if (s == NULL)
		s = "(null)";
	ftpf_string_countlen(ft_strlen(s), param);
	if (!(param->conv->flags & FTPF_MINUS))
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	ftpf_putpad('0', param->conv->zeropadlen, param);
	if (param->conv->datalen != 0)
		ftpf_write(s, param->conv->datalen, param);
	if (param->conv->flags & FTPF_MINUS)
		ftpf_putpad(' ', param->conv->spacepadlen, param);
	param->fmt++;
}
