/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:35:47 by mbascuna          #+#    #+#             */
/*   Updated: 2021/11/26 18:00:50 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;
	char			*tofind;

	str = (char *)haystack;
	tofind = (char *)needle;
	i = 0;
	if (!tofind[i])
		return (&str[i]);
	while (str[i] && (i < len))
	{
		j = 0;
		while ((str[i + j] == tofind[j]) && tofind[j] && i + j < len)
		{
			j++;
			if (!tofind[j])
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
