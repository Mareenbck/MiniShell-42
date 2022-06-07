/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:05:25 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/07 17:46:26 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expand_cmd(t_global *global, t_cmd *cmd, char **split_path)
{
	t_env *env;
	char *tmp;

	env = find_name(&global->head_env, &cmd->val[0][1], ft_strlen(&cmd->val[0][1]));
	if (!env)
	{
		ft_free_tab(global->env);
		ft_free_tab(split_path);
		ft_lst_clear(&global->head, free);
		ft_lst_clear2(&global->headcmd, free);
		ft_lst_clear3(&global->head_env, free);
		return (1);
	}
	// free(cmd->val[0]);
	tmp = ft_strdup(env->var_value);
	// ft_strcpy(cmd->val[0], env->var_value);
	if (ft_search_builtin(cmd, tmp, global) == 0)
		ft_free_tab(split_path);
	else
	{
		cmd->path = find_binary(split_path, env->var_value);
		if (!cmd->path)
			ft_expand_echo(cmd, global, cmd->val[0]);
	}
	ft_free_tab(global->env);
	free(tmp);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_lst_clear3(&global->head_env, free);
	return (0);
	// ft_free_tab(split_path);
}

void	ft_expand_args(t_global *global, t_cmd *cmd, int i)
{
	t_env *env;
	env = find_name(&global->head_env, &cmd->val[i][1], ft_strlen(&cmd->val[i][1]));
	if (env)
		ft_strcpy(cmd->val[i], env->var_value);
	// printf("expand args env : %s, val : %s\n", env->var_name, env->var_value);
}

int	ft_exe(t_global *global, t_cmd *cmd)
{
	char	**split_path;
	int i = 0;

	if (execve(cmd->val[0], cmd->val, global->env) == -1)
	{
		split_path = ft_split_envp(&global->head_env, "PATH");
		if (!split_path)
		{
			ft_lst_clear(&global->head, free);
			ft_lst_clear2(&global->headcmd, free);
			perror("Command Not Found1");
		}
		if (cmd->expand[i])
			return (ft_expand_cmd(global, cmd, split_path));
		else
		{
			cmd->path = find_binary(split_path, cmd->val[i]);
		}
		while (cmd->val[++i])
			if (cmd->expand[i])
				ft_expand_args(global, cmd, i);
		ft_signal(1);
		// printf("cmd->path : %s, cmd->val : %s\n", cmd->path, cmd->val[0]);
		if (cmd->path != NULL)
		{
			if (execve(cmd->path, cmd->val, global->env) == -1)
			{
				ft_lst_clear(&global->head, free);
				ft_lst_clear2(&global->headcmd, free);
				ft_lst_clear3(&global->head_env, free);
				ft_free_tab(global->env);
				perror("Command Not Found");
				return (1);
			}
		}
		else
		{
			ft_lst_clear(&global->head, free);
			ft_lst_clear2(&global->headcmd, free);
			ft_lst_clear3(&global->head_env, free);
			ft_free_tab(global->env);
			perror("Command Not Found");
		}
	}
	return (0);
}

int	ft_search_builtin(t_cmd *cmd, char *str, t_global *global)
{
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
		if (ft_search_builtin(cmd, cmd->val[0], global) == 1)
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
		if (ft_search_builtin(cmd, cmd->val[0], global) == 1 && cmd->val[0] != NULL)
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
	while (cmd->next)
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
