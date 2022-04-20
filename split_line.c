/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:12:35 by emcariot          #+#    #+#             */
/*   Updated: 2022/04/20 12:15:04 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_linked_list(t_line *line)
{
	char **tab;
	char *str;
	int i;
	int	j;

	tab = ft_split(str, '|');
	i = 0;
	while (tab[i] && line)
	{
		printf("tab[i] = %s", tab[i]);
		line->val = tab[i];
		i++;
		line = line->next;
	}
	return (str);
}

