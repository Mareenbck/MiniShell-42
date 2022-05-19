/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:05:25 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/18 09:55:30 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_expand_cmd(t_global *global, t_cmd *cmd, char **split_path)
{
	t_env *env;
	env = find_name(&global->head_env, cmd->val[0], ft_strlen(cmd->val[0]));
	if (!env)
		ft_error("Command not found", NOTFOUND);
	ft_strcpy(cmd->val[0], env->var_value);
	cmd->path = ft_join_envp(split_path, env->var_value);
}

void	ft_expand_args(t_global *global, char *cmd)
{
	t_env *env;
	env = find_name(&global->head_env, cmd, ft_strlen(cmd));
	ft_strcpy(cmd, env->var_value);
}

void	ft_exe(t_global *global, t_cmd *cmd)
{
	char	**split_path;
	int i = 0;
	// g_exit_status = SUCCESS;
	split_path = ft_split_envp(&global->head_env, "PATH");
	if (!split_path)
		ft_error("Command not found", NOTFOUND);
	if (cmd->expand[i])
		ft_expand_cmd(global, cmd, split_path);
	else
		cmd->path = ft_join_envp(split_path, cmd->val[i]);
	while (cmd->val[++i])
		if (cmd->expand[i])
			ft_expand_args(global, cmd->val[i]);
	if (!cmd->path)
		ft_error("Command not found", NOTFOUND);
	ft_free_tab(split_path);
	if (execve(cmd->path, cmd->val, global->env) == -1)
	{
		// ft_free_tab(cmd_args);
		ft_error("Error of execution", CANTEXEC);
	}
}

int	ft_search_builtin(t_cmd *cmd, t_global *global)
{
	if (cmd->val[0] == NULL)
		return (1);
	if (!ft_strncmp(cmd->val[0], "echo", 4))
		ft_echo(global->headcmd, global);
	else if (!ft_strncmp(cmd->val[0], "cd", 2))
		ft_cd(cmd, global);
	else if (!ft_strncmp(cmd->val[0], "env", 3))
		ft_env(global);
	else if (!ft_strncmp(cmd->val[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd->val[0], "export", 6))
		ft_export(cmd, global);
	else if (!ft_strncmp(cmd->val[0], "unset", 5))
		ft_unset(cmd, global);
	else if (!ft_strncmp(cmd->val[0], "exit", 4))
		ft_exit(global, cmd);
	else
	{
		g_exit_status = NOTFOUND;
		return (1);
	}
	return (0);
}


// void	ft_child2_process(t_cmd *cmd, int *fd_pipe)
// {
// 	close(cmd->next->fd_pipe[1]);
// 	if (dup2(cmd->next->fd_pipe[0], cmd->next->input) == -1)
// 		ft_error("Error", ERROR);
// 	close(cmd->next->fd_pipe[0]);
// }



void	ft_simple_exe(t_cmd *cmd, t_global *global)
{
	if (ft_search_builtin(cmd, global) == 1)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			ft_signal(1);
			if (cmd->input != 0)
			{
				dup2(cmd->input, 0);
				close(cmd->input);
			}
			if (cmd->output != 1)
			{
				dup2(cmd->output, 1);
				close(cmd->output);
			}
			ft_exe(global, cmd);
		}
		wait(&cmd->pid);
		ft_signal(2);
		// waitpid(cmd->pid, NULL, 0);
	}
}

// void	ft_child1_process(t_cmd *cmd)
// {
// 	close(cmd->fd_pipe[0]);
// 	if (dup2(cmd->fd_pipe[1], cmd->output) == -1)
// 		ft_error("Error", ERROR);
// 	close(cmd->fd_pipe[1]);
// 	close(cmd->next->fd_pipe[1]);
// 	if (dup2(cmd->next->fd_pipe[0], cmd->next->input) == -1)
// 		ft_error("Error", ERROR);
// 	close(cmd->next->fd_pipe[0]);
// }

void	handle_pipes(t_cmd *cmd)
{
	if (cmd->fd_pipe[1] != 1)
	{
		close(cmd->fd_pipe[0]);
		dup2(cmd->fd_pipe[1], cmd->output);
		close(cmd->fd_pipe[1]);
	}
	if (cmd->fd_pipe[0] != 0)
	{
		close(cmd->fd_pipe[1]);
		dup2(cmd->fd_pipe[0], cmd->next->input);
		close(cmd->fd_pipe[0]);
	}
	dprintf(2, "cmd input : %d, cmd output : %d\n", cmd->input, cmd->output);
}

int	child_process(t_cmd *cmd, t_global *global)
{
	printf("input : %d, output : %d, fd[0] : %d fd[1] : %d\n", cmd->input, cmd->output, cmd->fd_pipe[0], cmd->fd_pipe[1]);
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_error("Error fork", ERROR);
	if (cmd->pid == 0)
	{
		ft_signal(1);
		handle_pipes(cmd);
		if (ft_search_builtin(cmd, global) == 1)
			ft_exe(global, cmd);
		ft_signal(2);
	}
	return (0);
}

int	open_pipes(t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		if (pipe(cmd->fd_pipe) == -1)
			ft_error("Error Pipe", ERROR);
	}
	return (0);
}

void	ft_parent_process(t_global *global)
{
	t_cmd *cmd;

	cmd = global->headcmd;
	while (cmd->next)
	{
		close(cmd->fd_pipe[0]);
		close(cmd->fd_pipe[1]);
		// cmd->output = STDOUT_FILENO;
		// cmd->input = STDIN_FILENO;
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
}

void	parse_execution(t_global *global)
{
	t_cmd *cmd;
	// int fd_pipe[2];

	cmd = global->headcmd;
	while (cmd)
	{
		if (cmd->next != NULL)
		{
			open_pipes(cmd);
			child_process(cmd, global);
			// close_pipes(cmd);
			ft_parent_process(global);
		}
		else
			ft_simple_exe(cmd, global);
		cmd = cmd->next;
	}
	// ft_close(global);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_signal(2);
}
