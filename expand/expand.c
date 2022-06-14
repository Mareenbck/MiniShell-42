/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:26:40 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/14 16:09:03 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_cmd(char *str)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if ((ft_isalnum(str[i]) && str[i + 1] == '\'')
			|| (ft_isalnum(str[i]) && str[i - 1] == '$')
			|| (ft_isalnum(str[i]) && str[i - 1] == '='))
			words++;
		else if (str[i] == '\'')
			words++;
		i++;
	}
	return (words);
}

char	**split_expand(char *str)
{
	char	**split;
	int		words;

	str = ft_strtrim(str, "\"");
	words = ft_count_cmd(str);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	split = ft_fill_split_expand(str, words, split);
	free(str);
	split[words] = NULL;
	return (split);
}

void	ft_init_expand(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->val[1] != NULL)
	{
		while (cmd->val[i])
		{
			cmd->expand[i] = 0;
			i++;
		}
	}
}

int	ft_print_val(char **split, t_cmd *cmd)
{
	cmd->expand[0] = 0;
	ft_free_tab(split);
	return (1);
}

int	ft_expand_cmd_first(t_global *global)
{
	t_cmd	*cmd;
	char	**split;

	cmd = global->headcmd;
	while (cmd->next)
	{
		if (!ft_strchr(cmd->val[0], '$') || cmd->val[1] != NULL)
			break ;
		else if (!cmd->val[1])
		{
			split = ft_split_many(cmd->val[0], "$\"");
			if ((split[0] != NULL && split[1] == NULL) || split[0] == NULL)
			{
				return (ft_print_val(split, cmd));
			}
		}
		split = ft_create_cmd(split, global);
		ft_free_tab(cmd->val);
		cmd->val = ft_split(split[0], ' ');
		ft_init_expand(cmd);
		ft_free_tab(split);
		cmd = cmd->next;
	}
	return (0);
}
