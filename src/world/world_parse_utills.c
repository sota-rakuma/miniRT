#include "world.h"

bool	check_in_range(double val[], size_t len, double max, double min)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (val[i] < min || max < val[i])
			return (false);
		i++;
	}
	return (true);
}

bool	check_num_of_elements(char *str)
{
	char	*commma;
	long	cnt;

	cnt = 0;
	commma = str;
	while (true)
	{
		commma = ft_strchr(commma, ',');
		if (commma == NULL)
			break ;
		else if (!ft_isdigit(commma[1])
			&& commma[1] != '-' && commma[1] != '+')
			return (false);
		commma++;
		cnt++;
	}
	return (cnt == 2);
}
