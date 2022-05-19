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

int	cmd_list_len(t_cmd **head)
{
	t_cmd *cmd;
	cmd = *head;
	int len = 0;

	while (cmd)
	{
		len++;
		cmd = cmd->next;
	}
	return (len);
}

void	ft_child1_process(t_cmd *cmd, int *fd_pipe, t_global *global)
{
	int i;
	int len;

	i = 0;
	len = cmd_list_len(&global->headcmd);
	// while (i < len)
	// {
		// if (*cmd->index != i)
	close(cmd->fd_pipe[0]);
		// if (*cmd->index + 1 != i)
	close(cmd->next->fd_pipe[1]);
	// }
	// close(fd_pipe[*cmd->index][0]);
	if (dup2(cmd->fd_pipe[1], cmd->output) == -1)
		ft_error("Error", ERROR);
	close(fd_pipe[*cmd->index + 1][1]);
}

// void	ft_child2_process(t_cmd *cmd, int *fd_pipe)
// {
// 	close(fd_pipe[1]);
// 	if (dup2(fd_pipe[0], cmd->input) == -1)
// 		ft_error("Error", ERROR);
// 	close(fd_pipe[0]);
// }


void	ft_parent_process(int *fd_pipe, t_cmd *cmd, t_global *global)
{
	int len;
	int i;

	i = 0;
	len = cmd_list_len(&global->headcmd);
	(void)cmd;
	while (i <= len)
	{
		if (i != len -1)
			close(fd_pipe[i][0]);
		if (i != 0)
			close(fd_pipe[i][1]);
		i++;
	}
	close(fd_pipe[0][1]);
	close(fd_pipe[len][0]);
	// wait(&cmd->pid);
	i = 0;
	while (i < len)
	{
		if (wait(NULL) == -1)
			ft_error("Error waitpid", ERROR);
		i++;

	}
}

void	ft_simple_exe(t_cmd *cmd, t_global *global)
{
	if (ft_search_builtin(cmd, global) == 1)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			ft_signal(1);
			ft_exe(global, cmd);
		}
		ft_signal(2);
		wait(&cmd->pid);
	}
}


int	parse_execution(t_global *global)
{
	t_cmd *cmd;
	int len;
	int i;
	len = cmd_list_len(&global->headcmd);
	// int fd_pipe[len][2];
	i = 0;

	cmd = global->headcmd;
	while (i <= len)
	{
		if (pipe(cmd->fd_pipe) == -1)
			ft_error("Pipe Failed", PIPE_FAIL);
		i++;
	}
	while (cmd->next != NULL)
	{
		if (cmd->pipe)
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
			{
				ft_signal(1);
				ft_child1_process(cmd, cmd->fd_pipe, global);
				if (ft_search_builtin(cmd, global) == 1)
					ft_exe(global, cmd);
				ft_signal(2);
			}
			// cmd = cmd->next;
			// cmd->pid = fork();
			// if (cmd->pid == 0)
			// {
			// 	ft_signal(1);
			// 	ft_child2_process(cmd, fd_pipe);
			// 	if (ft_search_builtin(cmd, global) == 1)
			// 		ft_exe(global, cmd);
			// 	ft_signal(2);
			// }
			ft_parent_process(cmd->fd_pipe, cmd, global);
			// ft_signal(2);
		}
		else
			ft_simple_exe(cmd, global);
		cmd = cmd->next;
	}
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	// ft_signal(2);
	return (0);
}
