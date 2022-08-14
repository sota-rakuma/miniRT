#include "util.h"

bool	is_number(char *str)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	if (len == 0)
		return (false);
	if ((str[i] == '+' || str[i] == '-')
		&& ft_isdigit(str[i + 1]))
		i++;
	while (i < len)
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}
