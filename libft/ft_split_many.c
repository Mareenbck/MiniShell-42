/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_many.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:54:31 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/08 11:14:12 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char *str, char *charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (include_charset(str[i], charset) == 0
			&& include_charset(str[i + 1], charset) == 1)
			words++;
		i++;
	}
	return (words);
}

void	ft_strcpy_b(char *dest, char *str, char *charset)
{
	int	i;

	i = 0;
	while (include_charset(str[i], charset) == 0)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}

char	**ft_split_words(char *str, char *charset, char **split)
{
	int	words;
	int	i;
	int	j;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (include_charset(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (include_charset(str[i + j], charset) == 0)
				j++;
			if (j != 0)
				split[words] = (char *)malloc(sizeof(char) * (j + 1));
			ft_strcpy_b(split[words], &str[i], charset);
			i += j;
			words++;
		}
	}
	return (split);
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

char	**ft_split_many(char *str, char *charset)
{
	char	**res;
	int		words;
	char	**split;

	words = count_words(str, charset);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	split = ft_split_words(str, charset, res);
	if (!split)
		return (ft_free(split));
	res[words] = NULL;
	return (res);
}
