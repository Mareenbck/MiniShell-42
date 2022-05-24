/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:15:28 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/24 12:28:36 by emcariot         ###   ########.fr       */
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
	if (cmd->input != STDOUT_FILENO)
	{
		dup2(cmd->output, fd);
		close(fd);
		cmd->input = fd;
	}
	printf("HELLO\n");
	return (EXIT_SUCCESS);
}
