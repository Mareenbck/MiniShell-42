/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:05:25 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/01 17:10:05 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_cmd(t_global *global, t_cmd *cmd, char **split_path)
{
	t_env *env;
	env = find_name(&global->head_env, &cmd->val[0][1], ft_strlen(&cmd->val[0][1]));
	if (!env)
		ft_error("CMD NOT FOUND", NOTFOUND);
	// printf("env : %s\n", env->var_name);
	// ft_strcpy(cmd->val[0], env->var_value);
	if (ft_search_builtin(cmd, global) == 1)
	{
		cmd->path = find_binary(split_path, env->var_value);
		if (!cmd->path)
			ft_expand_echo(cmd, global, cmd->val[0]);
	}
	// ft_free_tab(split_path);
}

void	ft_expand_args(t_global *global, char *cmd)
{
	t_env *env;
	env = find_name(&global->head_env, &cmd[1], ft_strlen(&cmd[1]));
	ft_strcpy(cmd, env->var_value);
}

void	ft_exe(t_global *global, t_cmd *cmd)
{
	char	**split_path;
	int i = 0;

	split_path = ft_split_envp(&global->head_env, "PATH");
	if (!split_path)
	{
		ft_lst_clear(&global->head, free);
		ft_lst_clear2(&global->headcmd, free);
		ft_error("Command not found1", NOTFOUND);
	}
	if (cmd->expand[i])
	{
		ft_expand_cmd(global, cmd, split_path);
	}
	else
	{
		cmd->path = find_binary(split_path, cmd->val[i]);
	}
	while (cmd->val[++i])
		if (cmd->expand[i])
			ft_expand_args(global, cmd->val[i]);
	ft_signal(1);
	if (execve(cmd->path, cmd->val, global->env) == -1)
	{
		ft_lst_clear(&global->head, free);
		ft_lst_clear2(&global->headcmd, free);
		//ft_error("Command Not Found", CANTEXEC);
	}
}

int	ft_search_builtin(t_cmd *cmd, t_global *global)
{
	if (cmd->val[0] == NULL)
		return (1);
	if (!ft_strncmp(cmd->val[0], "echo", 4))
		ft_echo(cmd, global);
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

void	init_io(t_cmd *cmd)
{
	if (cmd->input != STDIN_FILENO)
	{
		dup2(cmd->input, STDIN_FILENO);
		close(cmd->input);
	}
	if (cmd->output != STDOUT_FILENO)
	{
		dup2(cmd->output, STDOUT_FILENO);
		close(cmd->output);
	}
}

void	ft_exe_with_pipe(t_cmd *cmd, t_global *global)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_error("Error fork", ERROR);
	if (cmd->pid == 0)
	{
		// ft_signal(1);
		init_io(cmd);
		if (ft_search_builtin(cmd, global) == 1)
			ft_exe(global, cmd);
		exit(0);
	}
}

void	ft_child_process(t_cmd *cmd, t_global *global)
{
	if (cmd->prev)
		ft_exe_with_pipe(cmd, global);
	else
	{
		if (ft_search_builtin(cmd, global) == 1 && cmd->val[0] != NULL)
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
			{
				init_io(cmd);
				ft_exe(global, cmd);
				exit(0);
			}
		}
	}
}

void	ft_parent_process(t_global *global)
{
	t_cmd *cmd;

	cmd = global->headcmd;
	while (cmd->next != NULL)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
}

void	parse_execution(t_global *global)
{
	t_cmd *cmd;
	int fd_pipe[2];

	cmd = global->headcmd;
	while (cmd)
	{
		if (cmd->pipe)
		{
			if (pipe(fd_pipe) == -1)
				ft_error("Error Pipe", ERROR);
			cmd->output = fd_pipe[1];
			cmd->next->input = fd_pipe[0];
			ft_exe_with_pipe(cmd, global);
			if (cmd->input != STDIN_FILENO)
				close(cmd->input);
		}
		else
			ft_child_process(cmd, global);
		if (cmd->output != STDOUT_FILENO)
			close(cmd->output);
		cmd = cmd->next;
	}
	ft_parent_process(global);
	ft_lst_clear2(&global->headcmd, free);
	ft_lst_clear(&global->head, free);
	// ft_signal(2);
}
