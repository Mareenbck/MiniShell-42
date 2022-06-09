/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:12:10 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/09 17:18:49 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close(t_global *global)
{
	t_cmd	*cmd;

	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	cmd = global->headcmd;
	if (cmd)
	{
		while (cmd->next)
		{
			if (cmd->input != STDIN_FILENO)
				close(cmd->input);
			if (cmd->output != STDOUT_FILENO)
				close(cmd->output);
			if (cmd->pipe)
				close(cmd->next->input);
			cmd = cmd->next;
		}
	}
}

void	ft_close_cmd(t_global *global)
{
	t_cmd	*cmd;

	cmd = global->headcmd;
	if (cmd)
	{
		while (cmd->next)
		{
			if (cmd->input != STDIN_FILENO)
				close(cmd->input);
			if (cmd->output != STDOUT_FILENO)
				close(cmd->output);
			cmd = cmd->next;
		}
	}
}

void	ft_quit(t_global *global)
{
	printf("exit\n");
	ft_close(global);
	global->exit = 1;
	ft_free_list(global);
	exit(0);
}
