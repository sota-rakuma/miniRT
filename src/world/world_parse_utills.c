#include "../minirt.h"

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

bool	check_comma_cnt(char *str)
{
	char	*comma;
	long	cnt;

	cnt = 0;
	comma = str;
	while (true)
	{
		comma = ft_strchr(comma, ',');
		if (comma == NULL)
			break ;
		comma++;
		cnt++;
	}
	return (cnt == 2);
}

bool	check_num_cnt(char **strs)
{
	const size_t	size = strs_len(strs);
	size_t			len;
	size_t			i;
	size_t			j;

	if (size != 3)
		return (false);
	i = 0;
	while (i < size)
	{
		j = 0;
		len = ft_strlen(strs[i]);
		if (len == 0)
			return (false);
		if ((strs[i][j] == '+' || strs[i][j] == '-')
			&& ft_isdigit(strs[i][j + 1]))
			j++;
		while (j < len)
			if (!ft_isdigit(strs[i][j++]))
				return (false);
		i++;
	}
	return (true);
}

bool	check_filename(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 3)
		return (false);
	return (!ft_strncmp(&filename[len - 3], ".rt", 4));
}
