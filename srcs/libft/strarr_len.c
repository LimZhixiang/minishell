#include "libft.h"

int	strarr_len(char **strarr)
{
	int	i;

	i = 0;
	if (strarr == NULL)
		return (0);
	while (strarr[i])
		i++;
	return(i);
}