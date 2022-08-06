#include "../minirt.h"
#include <stdarg.h>
#include <stdio.h>

void	ft_printf_and_exit(int status, char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
	exit(status);
}
