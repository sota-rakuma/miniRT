#include "../minirt.h"
#include <stdio.h>

void	error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	error_line_msg(long row, char *msg)
{
	printf("Error\nin %ld: %s\n", row, msg);
	exit(1);
}
