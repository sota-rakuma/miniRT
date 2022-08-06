#include "util.h"

void	free_all(char **strs)
{
	long	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}
