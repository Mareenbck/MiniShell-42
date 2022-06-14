/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:17 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/14 16:09:33 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_go_expand_echo(t_cmd *cmd, t_global *global, char *tmp)
{
	ft_expand_echo(cmd, global, cmd->val[0]);
	free(tmp);
	ft_free_list(global);
	return (1);
}

int	ft_find_j(int j, int i, char *str)
{
	if (str[i] == '$' || str[i] == '=')
	{
		j++;
		while (ft_isalnum(str[j]))
			j++;
	}
	return (j);
}

char	**ft_fill_split_expand(char *str, int words, char **split)
{
	int		k;
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	k = -1;
	while (++k < words)
	{
		j = ft_find_j(j, i, str);
		tmp = ft_strdup_bis(&str[(i)], j - i);
		split[k] = ft_strtrim(tmp, "\"\'");
		free(tmp);
		if (str[j++] == '\'')
			split[++k] = ft_strdup("\'");
		else
			j--;
		i += j - i;
	}
	return (split);
}
