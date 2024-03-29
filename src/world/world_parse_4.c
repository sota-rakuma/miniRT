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

double	parse_positive_num(char *str, long row)
{
	double	num;
	char	buf[1024];

	num = parse_num(str, row);
	if (num <= 0.0)
	{
		ft_strlcpy(buf, str, 1024);
		ft_strlcat(buf, " is not positive number", 1024);
		error_line_msg(row, buf);
	}
	return (num);
}

t_vec3d	parse_vec3d(char *str, long row)
{
	char	**strs;
	t_vec3d	vec;

	strs = ft_split(str, ',');
	if (!check_comma_cnt(str) || !check_elements(strs, FLOAT))
		error_line_msg(row, "vector has wrong elements");
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

	strs = ft_split(str, ',');
	if (!check_comma_cnt(str) || !check_elements(strs, INTEGER))
		error_line_msg(row, "color has wrong elements");
	color.r = parse_num(strs[0], row);
	color.g = parse_num(strs[1], row);
	color.b = parse_num(strs[2], row);
	if (!check_in_range((double []){color.r, color.g, color.b}, 3, 255.0, 0.0))
		error_line_msg(row, "color is out of range");
	free_all(strs);
	return (color);
}
