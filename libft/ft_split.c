/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:43:58 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/08 11:11:39 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (((s[i] != c) && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static char	*ft_strncpy(char *dst, const char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	**ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	**ft_split_words(char const *s, char c, char **split)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] && s[i + j] != c)
				j++;
			split[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (!split[word])
				return (ft_free(split));
			ft_strncpy(split[word], &s[i], j);
			i += j;
			word++;
		}
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**split;

	words = count_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (ft_free(split));
	split = ft_split_words(s, c, split);
	if (!split)
		return (ft_free(split));
	split[words] = NULL;
	return (split);
}
