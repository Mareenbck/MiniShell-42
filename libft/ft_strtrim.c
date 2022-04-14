/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:02:38 by mbascuna          #+#    #+#             */
/*   Updated: 2021/11/26 18:35:20 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && (ft_strchr(set, s1[i]) != 0))
		i++;
	return (i);
}

static int	ft_end(char const *s1, char const *set)
{
	int	j;

	j = ft_strlen(s1);
	while (s1[j - 1] && (ft_strchr(set, s1[j - 1]) != 0))
		j--;
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		start;
	int		end;
	int		size;

	if (!set || !s1)
		return (NULL);
	size = ft_strlen(s1);
	start = ft_start(s1, set);
	if (start >= size)
		return (ft_strdup(""));
	end = ft_end(s1, set);
	str = malloc(sizeof(char) * end - start + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
