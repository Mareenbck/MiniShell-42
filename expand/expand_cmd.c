/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:11:15 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/14 10:28:53 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			return (ft_go_expand_echo(cmd, global, tmp));
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

void	ft_print_split_env(t_cmd *cmd, t_global *global, char **split)
{
	int		i;
	t_env	*env;

	i = 0;
	env = global->head_env;
	while (split[i])
	{
		if (!ft_strchr(split[i], '$'))
			env = find_name(&global->head_env, split[i], ft_strlen(split[i]));
		else
			env = find_name(&global->head_env,
					&split[i][1], ft_strlen(&split[i][1]));
		if (env)
			write(cmd->output, env->var_value, ft_strlen(env->var_value));
		else if (!env && split[i][0] != '$')
			write(cmd->output, split[i], ft_strlen(split[i]));
		i++;
	}
}

void	ft_expand_echo(t_cmd *cmd, t_global *global, char *str)
{
	char	**split;
	char	*tmp;

	if (cmd->val[1] != NULL && cmd->val[1][1] == '?')
	{
		tmp = ft_itoa(g_exit_status);
		write(1, tmp, ft_strlen(tmp));
		free(tmp);
	}
	else if (str[0] == '$' && !str[1])
	{
		g_exit_status = 127;
		ft_free_list2(global);
	}
	else
	{
		split = split_expand(str);
		ft_print_split_env(cmd, global, split);
		ft_free_tab(split);
	}
}
