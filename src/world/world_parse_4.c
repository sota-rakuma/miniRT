#include "../minirt.h"

double	parse_num(char *str, long row)
{
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
		error_line_msg(row, "parse_num error");
	return (sign * integer);
}

t_vec3d	parse_vec3d(char *str, long row)
{
	char	**strs;
	t_vec3d	vec;

	if (!check_num_of_elements(str))
		error_line_msg(row, "vector has wrong number of elements");
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
	t_color	color;

	if (!check_num_of_elements(str))
		error_line_msg(row, "color has wrong number of elements");
	strs = ft_split(str, ',');
	color.r = parse_num(strs[0], row);
	color.g = parse_num(strs[1], row);
	color.b = parse_num(strs[2], row);
	if (!check_in_range((double []){color.r, color.g, color.b}, 3, 255.0, 0.0))
		error_line_msg(row, "color is out of range");
	free_all(strs);
	return (color);
}
