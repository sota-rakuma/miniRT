#include "util.h"

void	*ft_xalloc(size_t count, size_t size, const char *func_name)
{
	size_t	ratio;
	size_t	len;
	void	*ptr;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	ratio = ULONG_MAX / size;
	if (count > ratio)
		len = ULONG_MAX;
	else
		len = size * count;
	ptr = malloc(len);
	if (ptr == NULL)
	{
		printf("in %s, failed to malloc\nError\n", func_name);
		exit(1);
	}
	return (ptr);
}
