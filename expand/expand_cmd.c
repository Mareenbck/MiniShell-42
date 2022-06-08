/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:11:15 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/08 21:20:54 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_expand_cmd(t_global *global, t_cmd *cmd, char **split_path)
{
	t_env	*env;
	char	*tmp;

	env = find_name(&global->head_env,
			&cmd->val[0][1], ft_strlen(&cmd->val[0][1]));
	if (!env)
	{
		ft_free_tab(global->env);
		ft_free_tab(split_path);
		perror("Command not Found");
		return (1);
	}
	tmp = ft_strdup(env->var_value);
	if (ft_search_builtin(cmd, tmp, global) == 0)
		ft_free_tab(split_path);
	else
	{
		cmd->path = find_binary(split_path, env->var_value);
		if (!cmd->path)
		{
			ft_expand_echo(cmd, global, cmd->val[0]);
			free(tmp);
			ft_free_list(global);
			return (1);
		}
	}
	free(tmp);
	ft_free_list(global);
	return (0);
}

void	ft_expand_args(t_global *global, t_cmd *cmd, int i)
{
	t_env	*env;

	env = find_name(&global->head_env,
			&cmd->val[i][1], ft_strlen(&cmd->val[i][1]));
	if (env)
		ft_strcpy(cmd->val[i], env->var_value);
}

void	ft_expand_echo(t_cmd *cmd, t_global *global, char *str)
{
	t_env	*env;
	char	**split;
	int		i;

	env = global->head_env;
	if (cmd->val[1] != NULL && cmd->val[1][1] == '?')
		printf("%d", g_exit_status);
	else if (str[0] == '$' && !str[1])
	{
		g_exit_status = 127;
		ft_free_only_list(global);
	}
	else
	{
		split = split_expand(str);
		i = 0;
		while (split[i])
		{
			if (!ft_strchr(split[i], '$'))
				env = find_name(&global->head_env, split[i], ft_strlen(split[i]));
			else
				env = find_name(&global->head_env, &split[i][1], ft_strlen(&split[i][1]));
			if (env)
				printf("%s", env->var_value);
			else if (!env && split[i][0] != '$')
				printf("%s", split[i]);
			i++;
		}
		ft_free_tab(split);
	}
}
