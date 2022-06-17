/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:15:28 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/17 15:15:57 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	append_out(t_cmd *cmd, char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
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
