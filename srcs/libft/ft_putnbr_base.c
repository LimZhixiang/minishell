/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraynen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:10:20 by yraynen           #+#    #+#             */
/*   Updated: 2023/09/06 16:10:45 by yraynen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	basevalid(char *base)
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

void	ft_putnbr(int nb, int base, char *basev)
{
	long	longnb;

	longnb = nb;
	if (longnb < 0)
	{
		write(1, "-", 1);
		longnb *= -1;
		ft_putnbr(longnb, base, basev);
	}
	else if (longnb >= base)
	{
		ft_putnbr(longnb / base, base, basev);
		ft_putchar(basev[longnb % base]);
	}
	else
		ft_putchar(basev[longnb]);
}

void	ft_putnbr_base(int nb, char *base)
{
	int	i;

	i = 0;
	if (basevalid(base))
	{
		while (base[i])
			i++;
		ft_putnbr(nb, i, base);
	}
}
