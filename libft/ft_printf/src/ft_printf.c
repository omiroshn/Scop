/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <omiroshn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:39:22 by omiroshn          #+#    #+#             */
/*   Updated: 2018/01/30 18:23:40 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_dprintf(int fd, const char *msg, ...)
{
	t_info	info;
	t_num	n;

	info.res = 0;
	info.fd = fd;
	init_flags(&info, &n);
	va_start(info.valist, msg);
	info.res = parse_argument(msg, &info, n);
	va_end(info.valist);
	return (info.res);
}

int			ft_printf(const char *msg, ...)
{
	t_info	info;
	t_num	n;

	info.res = 0;
	info.fd = 1;
	init_flags(&info, &n);
	va_start(info.valist, msg);
	info.res = parse_argument(msg, &info, n);
	va_end(info.valist);
	return (info.res);
}
