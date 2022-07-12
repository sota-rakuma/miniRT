#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*gen_str(char *b, int size_b)
{
	char	*a;

	int	size = (size_b * (size_b + 1) / 2 + 1);
	a = (char *)malloc(sizeof(char) * size);
	a[size - 1] = '\0';
	int	index = 0;
	for (size_t i = 0; i < size_b; i++)
	{
		size_t j = 0;
		for (; j <= i; j++)
		{
			a[index + j] = b[j];
		}
		index+=j;
	}
	return (a);
}

int	main(void)
{
	//abcdefghijklmnopqrstuvwxyz
	char	*a = gen_str("1234567890abcdefghijklmn", 25);
	printf("%s\n", a);
	char	*c = ft_strnstr(a, "1234567890abcdefghijklmn", strlen(a));
	if (c)
		printf("YES: %s\n", c);
	else
		printf("NO\n");
	free(a);
	return (0);
}
