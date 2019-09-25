/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 20:44:16 by omiroshn          #+#    #+#             */
/*   Updated: 2018/05/12 20:44:16 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			*my_itoa(intmax_t n)
{
	char		*str;
	intmax_t	temp;
	intmax_t	len;
	intmax_t	minus;

	len = ((n <= 0) ? 1 : 0);
	minus = ((n < 0) ? -1 : 1);
	temp = n;
	while (++len && temp)
		temp /= 10;
	if (!(str = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	str[--len] = '\0';
	*str = '0';
	temp = n;
	while (temp)
	{
		str[--len] = '0' + (minus) * (temp % 10);
		temp /= 10;
	}
	if (n < 0)
		*str = '-';
	return (str);
}

inline static void	print_aa(t_info *info, t_num *n, const char *str, int i)
{
	n->imaxt = ft_cast_int(n->imaxt, info, str, i);
	n->prec = info->precision;
	if (info->star && info->width < 0)
	{
		info->minus = 1;
		info->width = -info->width;
	}
	if (info->width > 0)
		info->width -= ft_intlen(n->imaxt);
	if (info->width && n->imaxt == 0 && n->prec == 0 && info->dot)
		info->width++;
	if (info->precision > 0)
	{
		info->precision -= ft_intlen(n->imaxt);
		n->imaxt < 0 ? info->precision++ : 0;
		info->width = info->precision > 0 ?
			info->width - info->precision : info->width;
	}
	if ((n->imaxt >= 0 && info->plus)
		|| (n->imaxt >= 0 && info->space && info->zero && info->width > 0))
		info->width--;
}

inline static void	print_bb(t_info *info, t_num *n)
{
	if (info->width > 0)
		info->res += info->width;
	if (info->precision > 0)
		info->res += info->precision;
	n->wid = info->width;
	if ((n->imaxt >= 0 && info->space && !info->width)
		|| (n->imaxt >= 0 && info->space && info->zero && info->width > 0))
	{
		write(info->fd, " ", 1);
		info->res++;
	}
	if (!info->minus && !info->zero)
		while (info->width-- > 0)
			write(info->fd, " ", 1);
	if (n->imaxt >= 0 && info->plus)
	{
		write(info->fd, "+", 1);
		info->res++;
	}
}

inline static void	print_cc(t_info *info, t_num *n)
{
	if (!info->minus && info->zero && info->precision <= 0)
	{
		if (n->imaxt < 0)
		{
			write(info->fd, "-", 1);
			n->imaxt *= -1;
			info->res++;
		}
		while (info->width-- > 0)
			write(info->fd, "0", 1);
	}
	else if (!info->minus && info->zero)
		while (info->width-- > 0)
			write(info->fd, " ", 1);
	if (n->imaxt < 0 && (unsigned long)n->imaxt != -9223372036854775808U)
	{
		write(info->fd, "-", 1);
		n->imaxt *= -1;
		info->res++;
	}
}

int					print_d(t_info *info, t_num n, const char *str, int i)
{
	print_aa(info, &n, str, i);
	print_bb(info, &n);
	print_cc(info, &n);
	while (info->precision-- > 0)
		write(info->fd, "0", 1);
	if (n.imaxt == 0 && n.prec == 0 && info->dot)
		return (i);
	n.s = my_itoa(n.imaxt);
	ft_putstr(n.s);
	info->res += ft_intlen(n.imaxt);
	if (info->minus)
		while (n.wid-- > 0)
			write(info->fd, " ", 1);
	free(n.s);
	return (i);
}
