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

void	ft_exe(t_global *global)
{
	char	*cmd_path;
	char	**split_path;
	char	**cmd_args;

	cmd_args = global->headcmd->val;
	split_path = ft_split_envp(&global->head_env);
	if (!split_path)
		ft_error("Variable not found");
	cmd_path = ft_join_envp(split_path, cmd_args[0]);
	if (!cmd_path)
		ft_error("command not found");
	ft_free_tab(split_path);
	printf("cmd path %s\n", cmd_path);
	if (execve(cmd_path, cmd_args, global->env) == -1)
	{
		ft_free_tab(cmd_args);
		ft_error("Error of execution");
	}
}

int	ft_search_builtin(t_token *token, t_global *global)
{
	if (token->val == NULL)
		return (1);
	if (!ft_strncmp(token->val, "echo", 4))
		ft_echo(token->next, &global->head_env);
	else if (!ft_strncmp(token->val, "cd", 2))
		ft_cd(token->next, global);
	else if (!ft_strncmp(token->val, "env", 3))
		ft_env(global);
	else if (!ft_strncmp(token->val, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(token->val, "export", 6))
		ft_export(token->next, &global->head_env);
	else
		return (1);
	return (0);
}

void	ft_execution(t_global *global)
{
	pid_t	pid;

	// ft_signal(0);
	if (ft_search_builtin(global->head, global) == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_signal(1);
			ft_exe(global);
		}
		wait(&pid);
	}
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_signal(2);
}
