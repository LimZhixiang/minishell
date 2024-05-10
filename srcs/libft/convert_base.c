/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	basevalid_conv(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (base[i])
	{
		j = i + 1;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i <= 1)
		return (0);
	return (1);
}

char	*ft_putnbr_convert(int nb, char *basev, char *ret, int *i)
{
	long	longnb;

	longnb = nb;
	if (longnb < 0)
	{
		ret[(*i)++] = '-';
		longnb *= -1;
		ft_putnbr_convert(longnb, basev, ret, i);
	}
	else if (longnb >= (long)ft_strlen(basev))
	{
		ret[(*i)++] = basev[longnb % ft_strlen(basev)];
		ft_putnbr_convert(longnb / ft_strlen(basev), basev, ret, i);
	}
	else
	{
		ret[(*i)++] = basev[longnb % ft_strlen(basev)];
		ret[*i] = '\0';
	}
	return (ret);
}

int	ft_malloc_nb(int nb, int base, char *basev, int *i)
{
	long	longnb;

	longnb = nb;
	if (longnb < 0)
	{
		(*i)++;
		longnb *= -1;
		(*i) = ft_malloc_nb(longnb, base, basev, i);
	}
	else if (longnb >= base)
	{
		(*i)++;
		(*i) = ft_malloc_nb(longnb / base, base, basev, i);
	}
	else
		(*i)++;
	return (*i);
}

char	*ft_convert_base(int nb, char *base)
{
	int		i;
	int		j;
	char	*ret;

	j = 0;
	i = 0;
	if (basevalid_conv(base))
	{
		while (base[i])
			i++;
		j = ft_malloc_nb(nb, i, base, &j);
		ret = malloc(sizeof(char) * j + 1);
		if (ret == NULL)
			return (NULL);
		j = 0;
		ret = ft_putnbr_convert(nb, base, ret, &j);
		return (ret);
	}
	return (NULL);
}
