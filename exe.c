/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:05:25 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/29 12:05:39 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_cmd(t_global *global, t_cmd *cmd, char **split_path)
{
	t_env *env;

	env = find_name(&global->head_env, cmd->val[0]);
	ft_strcpy(cmd->val[0], env->var_value);
	cmd->path = ft_join_envp(split_path, env->var_value);
}

void	ft_expand_args(t_global *global, t_cmd *cmd, int i)
{
	t_env *env;

	env = find_name(&global->head_env, cmd->val[i]);
	ft_strcpy(cmd->val[i], env->var_value);
}

void	ft_exe(t_global *global)
{
	char	**split_path;
	t_cmd *cmd;
	int i = 0;

	cmd = global->headcmd;
	split_path = ft_split_envp(&global->head_env, "PATH");
	if (!split_path)
		ft_error("Variable not found");
	if (cmd->expand[i])
		ft_expand_cmd(global, cmd, split_path);
	else
		cmd->path = ft_join_envp(split_path, cmd->val[i]);
	while (cmd->val[++i])
		if (cmd->expand[i])
			ft_expand_args(global, cmd, i);
	if (!cmd->path)
		ft_error("Variable not found");
	// {
	// 	global->exit_status = NOTFOUND;
	// 	global->exit = 1;
	// }
	ft_free_tab(split_path);
	if (execve(cmd->path, cmd->val, global->env) == -1)
	{
		// ft_free_tab(cmd_args);
		ft_error("Error of execution");
	}
}

int	ft_search_builtin(t_token *token, t_global *global)
{
	if (token->val == NULL)
		return (1);
	if (!ft_strncmp(token->val, "echo", 4))
		ft_echo(token->next, global);
	else if (!ft_strncmp(token->val, "cd", 2))
		ft_cd(token->next, global);
	else if (!ft_strncmp(token->val, "env", 3))
		ft_env(global);
	else if (!ft_strncmp(token->val, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(token->val, "export", 6))
		ft_export(token->next, global);
	// else if (!ft_strncmp(token->val, "unset", 5))
	// 	ft_unset(token->next, global);
	else if (!ft_strncmp(token->val, "exit", 4))
		ft_exit(global, token->next);
	else
	{
		global->exit_status = 127;
		return (1);
	}
	return (0);
}

void	ft_execution(t_global *global)
{
	pid_t	pid;

	if (ft_search_builtin(global->head, global) == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_signal(1, global);
			ft_exe(global);
		}
		wait(&pid);
	}
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_signal(2, global);
}
