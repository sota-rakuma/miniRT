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

bool	check_elements(char **strs, t_check kind)
{
	const size_t	size = strs_len(strs);
	size_t			i;

	if (size != 3)
		return (false);
	i = 0;
	while (i < size)
	{
		if (kind == INTEGER && !is_number(strs[i]))
			return (false);
		else if (kind == FLOAT && !is_float(strs[i]))
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
