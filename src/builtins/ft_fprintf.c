/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:21:03 by breda-si          #+#    #+#             */
/*   Updated: 2025/03/10 09:22:23 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	char	*str;
	char	*arg_str;

	va_start(args, format);
	str = (char *)format;
	while (*str)
	{
		if (*str == '%' && *(str + 1) == 's')
		{
			arg_str = va_arg(args, char *);
			write(fd, arg_str, ft_strlen(arg_str));
			str += 2;
		}
		else
		{
			write(fd, str, 1);
			str++;
		}
	}
	va_end(args);
}
