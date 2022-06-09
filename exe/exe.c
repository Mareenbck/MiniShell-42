/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:05:25 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/09 13:36:06 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execve(t_global *global, t_cmd *cmd)
{
	char	**split_path;
	int		i;

	i = 0;
	if (execve(cmd->val[0], cmd->val, global->env) == -1)
	{
		split_path = ft_split_envp(&global->head_env, "PATH");
		if (!split_path)
			return (ft_free_list_and_error(global));
		if (cmd->expand[i])
			return (ft_expand_cmd(global, cmd, split_path));
		else
			cmd->path = find_binary(split_path, cmd->val[i]);
		if (!cmd->path)
			return (ft_free_list_and_error(global));
		while (cmd->val[++i])
			if (cmd->expand[i])
				ft_expand_args(global, cmd, i);
		ft_signal(1);
		if (execve(cmd->path, cmd->val, global->env) == -1)
			return (ft_free_list_and_error(global));
	}
	return (0);
}

int	ft_search_builtin(t_cmd *cmd, char *str, t_global *global)
{
	ft_signal(3);
	if (str == NULL)
		return (1);
	if (!ft_strncmp(str, "echo", 5))
		ft_echo(cmd, global);
	else if (!ft_strncmp(str, "cd", 3))
		ft_cd(cmd, global);
	else if (!ft_strncmp(str, "env", 4))
		ft_env(global);
	else if (!ft_strncmp(str, "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(str, "export", 7))
		ft_export(cmd, global);
	else if (!ft_strncmp(str, "unset", 6))
		ft_unset(cmd, global);
	else if (!ft_strncmp(str, "exit", 5))
		ft_exit(global, cmd);
	else
	{
		return (1);
	}
	return (0);
}

void	ft_exe_with_pipe(t_cmd *cmd, t_global *global)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		perror("Error fork");
	if (cmd->pid == 0)
	{
		init_io(cmd);
		if (ft_search_builtin(cmd, cmd->val[0], global) == 1)
		{
			if (ft_execve(global, cmd))
			{
				ft_close(global);
				close(3);
				ft_free_list2(global);
				exit(127);
			}
		}
		ft_close(global);
		ft_free_list(global);
		exit(0);
	}
}

void	ft_child_process(t_cmd *cmd, t_global *global)
{
	if (cmd->prev)
		ft_exe_with_pipe(cmd, global);
	else
	{
		if (ft_search_builtin(cmd, cmd->val[0], global) == 1
			&& cmd->val[0] != NULL)
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
			{
				init_io(cmd);
				if (ft_execve(global, cmd))
				{
					// printf("\n");
					//POUR LE $PATH
					ft_close(global);
					ft_free_list2(global);
					exit(127);
				}
				ft_close(global);
				ft_free_list2(global);
				exit(0);
			}
		}
	}
}

void	ft_parent_process(t_global *global)
{
	t_cmd	*cmd;

	cmd = global->headcmd;
	while (cmd->next != NULL)
	{
		waitpid(cmd->pid, &g_exit_status, 0);
		if (g_exit_status == 131 && ft_strncmp(cmd->val[0], "echo", 4))
			printf("Quit (core dumped)\n");
		cmd = cmd->next;
	}
	if (global->exit == -1)
		g_exit_status = 1;
	else if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else
		g_exit_status = WTERMSIG(g_exit_status) + 128;
}
