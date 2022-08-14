#include "util.h"

bool	is_float(char *str)
{
	bool	flag;
	char	*integer;
	char	*decimal;

	decimal = ft_strchr(str, '.');
	if (decimal)
		integer = ft_substr(str, 0, decimal - str);
	else
		integer = ft_strdup(str);
	if (integer == NULL)
		exit(1);
	flag = is_number(integer);
	free(integer);
	if (decimal == NULL)
		return (flag);
	if (decimal[1] == '\0')
		return (false);
	while (*(++decimal))
	{
		if (!ft_isdigit(*decimal))
			return (false);
	}
	return (flag);
}
