/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:26:40 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/09 14:03:57 by mbascuna         ###   ########.fr       */
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
			|| (ft_isalnum(str[i]) && !str[i + 1]))
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
	char	*tmp;
	int		i;
	int		j;
	int		words;

	i = 0;
	str = ft_strtrim(str, "\"");
	words = ft_count_cmd(str);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	j = 0;
	while (i < words)
	{
		while (ft_isalnum(str[j]) || str[j] == '$')
			j++;
		tmp = ft_strdup_bis(&str[(j - (j - i))], j - i);
		split[i] = ft_strtrim(tmp, "\"\'");
		free(tmp);
		if (str[j++] == '\'')
			split[++i] = ft_strdup("\'");
		i++;
	}
	free(str);
	split[words] = NULL;
	return (split);
}

char	**ft_create_cmd(char **split, t_global *global)
{
	int		i;
	t_env	*env;

	i = 0;
	while (split[i] != NULL)
	{
		env = find_name(&global->head_env, split[i], ft_strlen(split[i]));
		if (env && i == 0)
		{
			free(split[0]);
			split[0] = ft_strdup(env->var_value);
		}
		else if (env && i > 0)
			split[0] = ft_strjoin(split[0], env->var_value);
		else if (i != 0)
			split[0] = ft_strjoin(split[0], split[i]);
		i++;
	}
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

void	ft_expand_cmd_first(t_global *global)
{
	t_cmd	*cmd;
	t_env	*env;
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
				env = find_name(&global->head_env, split[0], ft_strlen(split[0]));
				if (env)
					printf("%s : command not found\n", env->var_value);
				else
					write(2," ",1);
				ft_free_tab(split);
				break ;
			}
		}
		split = ft_create_cmd(split, global);
		ft_free_tab(cmd->val);
		cmd->val = ft_split(split[0], ' ');
		ft_init_expand(cmd);
		ft_free_tab(split);
		cmd = cmd->next;
	}
}
