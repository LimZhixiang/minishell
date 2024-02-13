#include "libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 12))
		return (1);
	return (0);
}