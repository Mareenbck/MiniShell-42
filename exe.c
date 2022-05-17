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

	env = find_name(&global->head_env, cmd->val[0], ft_strlen(cmd->val[0]));
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
	// t_cmd *cmd;
	int i = 0;

	// cmd = global->headcmd;
	split_path = ft_split_envp(&global->head_env, "PATH");
	// if (!split_path)
	// 	ft_error("Variable not found");
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
	else if (!ft_strncmp(cmd->val[0], "unset", 4))
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

// void	handle_pipes(t_cmd *cmd)
// {
// 	dup2(cmd->output, STDOUT_FILENO);
// 	dup2(cmd->input, STDIN_FILENO);
// 	if (cmd->next)
// 	{
// 		close(cmd->pipes[0]);
// 		dup2(cmd->pipes[1], cmd->output);
// 		close(cmd->pipes[1]);
// 	}
// 	// if (cmd->prev)
// 	// {
// 	// 	dup2(cmd->prev->pipes[0], cmd->input);
// 	// 	close(cmd->prev->pipes[0]);
// 	// }
// }

// void	ft_child1_process(t_files *fd, int *fd_pipe, char *av, char **envp)
// {
// 	if ((dup2(fd->infile, STDIN_FILENO)) == -1)
// 		ft_error("Error");
// 	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
// 		ft_error("Error");
// 	close(fd_pipe[0]);
// 	close(fd->infile);
// 	ft_execute(envp, av);
// }

void	ft_child1_process(t_cmd *cmd, int *fd_pipe)
{

	printf("OUTPUT AVANT : %d fd : %d\n", cmd->output, fd_pipe[0]);
	// dup2(fd_pipe[0], cmd->output);
	if ((dup2(fd_pipe[0], cmd->output)) == -1)
		ft_error("Error", ERROR);
	// if ((dup2(fd_pipe[1], cmd2->input)) == -1)
	// 	ft_error("Error", ERROR);
	close(cmd->output);
	// close(fd_pipe[1]);
	printf("OUTPUT APRES : %d fd : %d\n", cmd->output, fd_pipe[0]);
}

void	ft_child2_process(t_cmd *cmd2, int *fd_pipe)
{
	printf("OUTPUT AVANT : %d fd : %d\n", cmd2->input, fd_pipe[1]);

	if ((dup2(fd_pipe[1], cmd2->input)) == -1)
		ft_error("Error1", ERROR);
	printf("OUTPUT APRES : %d fd : %d\n", cmd2->input, fd_pipe[1]);

	// if (dup2(fd_pipe[0], cmd1->output) == -1)
	// 	ft_error("Error", ERROR);
	// close(fd_pipe[0]);
	close(cmd2->input);
}


void	ft_parent_process(int *fd_pipe, t_cmd *cmd1, t_cmd *cmd2)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	wait(&cmd1->pid);
	wait(&cmd2->pid);
}


void	ft_pipe_exe(t_cmd *cmd1, t_cmd *cmd2, t_global *global)
{
	int	fd_pipe[2];

	printf("cmd1 : %s, cmd2 : %s\n", cmd1->val[0], cmd2->val[0]);
	if (pipe(fd_pipe) == -1)
		ft_error("Pipe failed", PIPE_FAIL);
	printf("fd : %d  fd : %d\n", fd_pipe[0], fd_pipe[1]);
	cmd1->pid = fork();
	if (cmd1->pid == 0)
	{
		ft_signal(1);
		ft_child1_process(cmd1, fd_pipe);
		if (ft_search_builtin(cmd1, global) == 1)
			ft_exe(global, cmd1);
		ft_signal(2);
	}
	cmd2->pid = fork();
	if (cmd2->pid == 0)
	{
		ft_signal(1);
		ft_child2_process(cmd2, fd_pipe);
		if (ft_search_builtin(cmd2, global) == 1)
			ft_exe(global, cmd2);
		ft_signal(2);
	}
	ft_parent_process(fd_pipe, cmd1, cmd2);
}

void	ft_simple_exe(t_cmd *cmd, t_global *global)
{
	printf("SIMPLE EXE\n");
	if (ft_search_builtin(cmd, global) == 1)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			ft_signal(1);
			ft_exe(global, cmd);
		}
		wait(&cmd->pid);
	}
	ft_signal(2);
}

void	parse_execution(t_global *global)
{
	t_cmd *cmd;

	cmd = global->headcmd;
	// while (cmd != NULL)
	// {
		if (cmd->pipe)
			ft_pipe_exe(cmd, cmd->next, global);
		else
			ft_simple_exe(cmd, global);
	// 	cmd = cmd->next;
	// }
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_signal(2);
}
