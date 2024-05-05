#include "libft.h"

void	free_str_arr(char **result)
{
	int	i;

	i = 0;
	if (result == NULL)
		return ;
	while (result[i])
		free(result[i++]);
	free(result);
}
