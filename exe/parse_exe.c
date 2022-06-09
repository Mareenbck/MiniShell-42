/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:18:52 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/09 16:34:24 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_execution(t_global *global)
{
	t_cmd	*cmd;
	int		fd_pipe[2];

	cmd = global->headcmd;
	while (cmd->next)
	{
		if (cmd->pipe)
		{
			if (pipe(fd_pipe) == -1)
				perror("Error Pipe");
			cmd->output = fd_pipe[1];
			cmd->next->input = fd_pipe[0];
			ft_exe_with_pipe(cmd, global);
		}
		else
			ft_child_process(cmd, global);
		if (cmd->output != STDOUT_FILENO)
			close(cmd->output);
		cmd = cmd->next;
	}
	ft_parent_process(global);
	ft_close_cmd(global);
	ft_lst_clear2(&global->headcmd, free);
	ft_lst_clear(&global->head, free);
}
