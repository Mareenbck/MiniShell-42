/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:04:16 by mbascuna          #+#    #+#             */
/*   Updated: 2021/11/26 16:21:22 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_malloc(long int n)
{
	if (n < 0)
		n *= -1;
	if (n < 10)
		return (1);
	else
		return (1 + size_malloc(n / 10));
}

static char	*ft_is_neg(int neg, char *str)
{
	if (neg)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			neg;
	int			size;
	char		*str;

	nb = n;
	size = size_malloc(n);
	neg = 0;
	if (nb < 0)
	{
		neg = 1;
		nb *= -1;
		size++;
	}
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size > neg)
	{
		str[--size] = (nb % 10) + 48;
		nb /= 10;
	}
	str = ft_is_neg(neg, str);
	return (str);
}
