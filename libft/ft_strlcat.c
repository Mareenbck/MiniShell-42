/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marinebascunana <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:19:15 by marinebas         #+#    #+#             */
/*   Updated: 2021/11/29 13:21:57 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_d;
	size_t	i;

	len_d = ft_strlen(dst);
	if (!dst && !src)
		return (0);
	if (dstsize - 1 < len_d || dstsize == 0)
		return (dstsize + ft_strlen(src));
	i = 0;
	while (src[i] && ((len_d + i) < (dstsize - 1)))
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + ft_strlen(src));
}
