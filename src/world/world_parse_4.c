#include "../minirt.h"

double	parse_num(char *str, long row)
{
	const char	*original = str;
	double		integer;
	double		sign;
	double		digit;

	integer = 0;
	digit = 10;
	sign = 1.0;
	if (*str == '-' || *str == '+')
		sign = 1.0 - 2.0 * (*(str++) == '-');
	while (ft_isdigit(*str))
		integer = integer * 10 + (double)(*(str++) - '0');
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		integer += (double)(*(str++) - '0') / digit;
		digit *= 10;
	}
	if (*str != '\0')
	{
		printf("line %ld: parse_num error: %s\nError\n", row, original);
		exit(1);
	}
	return (sign * integer);
}

t_vec3d	parse_vec3d(char *str, long row)
{
	char	**strs;
	long	len;
	t_vec3d	vec;

	if (!check_num_of_elements(str))
	{
		printf("line %ld: vector has wrong number of elements\nError\n", row);
		exit(1);
	}
	strs = ft_split(str, ',');
	vec.x = parse_num(strs[0], row);
	vec.y = parse_num(strs[1], row);
	vec.z = parse_num(strs[2], row);
	free_all(strs);
	return (vec);
}

t_color	parse_color(char *str, long row)
{
	char	**strs;
	long	len;
	t_color	color;

	if (!check_num_of_elements(str))
		ft_printf_and_exit(
			1, "line %ld: color has wrong number of elements\nError\n", row);
	strs = ft_split(str, ',');
	color.r = parse_num(strs[0], row);
	color.g = parse_num(strs[1], row);
	color.b = parse_num(strs[2], row);
	if (!check_in_range((double []){color.r, color.g, color.b}, 3, 255.0, 0.0))
	{
		printf("line %ld: color is out of range\nError\n", row);
		exit(1);
	}
	free_all(strs);
	return (color);
}