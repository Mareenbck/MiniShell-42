/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:05:25 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/17 12:34:33 by emcariot         ###   ########.fr       */
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

void	ft_exe(t_global *global)
{
	char	**split_path;
	t_cmd *cmd;
	int i = 0;

	cmd = global->headcmd;
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

int	ft_search_builtin(t_token *token, t_global *global)
{
	while (token->next != NULL)
	{
		if (token->val == NULL)
			return (1);
		if (!ft_strncmp(token->val, "echo", 4))
			ft_echo(global->headcmd, global);
		else if (!ft_strncmp(token->val, "cd", 2))
			ft_cd(token->next, global);
		else if (!ft_strncmp(token->val, "env", 3))
			ft_env(global);
		else if (!ft_strncmp(token->val, "pwd", 3))
			ft_pwd();
		else if (!ft_strncmp(token->val, "export", 6))
			ft_export(token->next, global);
		else if (!ft_strncmp(token->val, "unset", 4))
			ft_unset(token->next, global);
		else if (!ft_strncmp(token->val, "exit", 4))
			ft_exit(global, token->next);
		else
		{
			g_exit_status = NOTFOUND;
			return (1);
		}
		token = token->next;
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

void	ft_child1_process(t_cmd *cmd, int *fd_pipe, t_global *global)
{
	if ((dup2(cmd->input, STDIN_FILENO)) == -1)
		ft_error("Error", ERROR);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		ft_error("Error", ERROR);
	close(fd_pipe[0]);
	close(cmd->input);
	ft_exe(global);
}

void	ft_child2_process(t_cmd *cmd, int *fd_pipe, t_global *global)
{
	if (dup2(cmd->output, STDOUT_FILENO) == -1)
		ft_error("Error", ERROR);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		ft_error("Error", ERROR);
	close(fd_pipe[1]);
	close(cmd->output);
	ft_exe(global);
}

void	ft_parent_process(int *fd_pipe)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (wait(NULL) == -1)
		ft_error("Error waitpid", PIPE_FAIL);
}


void	ft_execution(t_global *global)
{
	// pid_t	pid;
	int	fd_pipe[2];
	t_cmd *cmd;

	cmd = global->headcmd;
	if (pipe(fd_pipe) == -1)
		ft_error("Pipe failed", PIPE_FAIL);
	// while (cmd->next != NULL)
	// {
		if (ft_search_builtin(global->head, global) == 1)
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
			{
				ft_signal(1);
				ft_child1_process(cmd, fd_pipe, global);
				// ft_exe(global);
			}
			cmd->next->pid = fork();
			if (cmd->next->pid == 0)
			{
				ft_signal(1);
				ft_child2_process(cmd->next, fd_pipe, global);
				// ft_exe(global);
			}
			// wait(&pid);
		}
	// 	cmd = cmd->next;
	// }
	ft_parent_process(fd_pipe);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_signal(2);
}
