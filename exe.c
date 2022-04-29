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

void	ft_exe(t_global *global, char *line)
{
	char	*cmd;
	char	**split_path;
	char	**cmd_args;

	cmd_args = ft_split(line, ' ');
	if (!cmd_args)
		ft_error("Split failed");
	split_path = ft_split_envp(global->env);
	cmd = ft_join_envp(split_path, cmd_args[0]);
	if (!cmd)
		ft_error("command not found");
	// ft_free_tab(split_path);
	if (execve(cmd, cmd_args, global->env) == -1)
	{
		ft_free_tab(cmd_args);
		ft_error("Error of execution");
	}
}

int	ft_search_builtin(t_token *token, t_global *global)
{
	if (!ft_strncmp(token->val, "echo", 4))
		ft_echo(token->next);
	else if (!ft_strncmp(token->val, "cd", 2))
		ft_cd(token->next, global);
	else if (!ft_strncmp(token->val, "env", 3))
		ft_env(global);
	else
		return (1);
	return (0);
}

void	ft_execution(t_global *global, char *line)
{
	pid_t	pid;

	if (ft_search_builtin(global->head, global) == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_signal(1);
			ft_exe(global, line);
		}
		wait(&pid);
	}
	ft_lst_clear(&global->head, free);
}

