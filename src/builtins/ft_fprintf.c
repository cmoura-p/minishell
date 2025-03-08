#include "../../include/minishell.h"
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

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
