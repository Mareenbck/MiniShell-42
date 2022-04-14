/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:34:37 by mbascuna          #+#    #+#             */
/*   Updated: 2021/11/26 18:05:27 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char		*s2;
	size_t		i;

	s2 = (char *)s;
	i = 0;
	while (i < n)
	{
		if (s2[i] == (char)c)
			return (&s2[i]);
		i++;
	}
	return (0);
}
