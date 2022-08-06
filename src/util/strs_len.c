#include "util.h"

long	strs_len(char **strs)
{
	long	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}
