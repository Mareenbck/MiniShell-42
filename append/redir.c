/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:28:11 by emcariot          #+#    #+#             */
/*   Updated: 2022/09/27 09:51:51 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_out(t_cmd *cmd, char *file_name)
{
	int	fd;


	fd = open(file_name, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror(file_name);
		return (EXIT_FAILURE);
	}
	if (cmd->output != STDOUT_FILENO)
	{
		dup2(fd, cmd->output);
		close(cmd->output);
	}
	cmd->output = fd;
	return (EXIT_SUCCESS);
}

int	redir_in(t_cmd *cmd, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (cmd->input != STDIN_FILENO)
	{
		dup2(cmd->input, fd);
		close(cmd->input);
	}
	cmd->input = fd;
	return (EXIT_SUCCESS);
}

int	check_access(t_cmd *cmd, char *file_name)
{
	if (access(file_name, F_OK) != 0)
		return (1);
	else
	{
		redir_in(cmd, file_name);
		return (0);
	}
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
		if (cmd->pipe && cmd->next)
			close(cmd->next->input);
	}
}
