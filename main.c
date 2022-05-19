/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:33:53 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/18 09:57:25 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

void	ft_init_minishell(t_global *global, char **envp)
{
	global->head = NULL;
	global->headcmd = NULL;
	global->head_env = NULL;
	global->exit = false;
	ft_init_env(global, envp);
	ft_init_list_env(&global->head_env, global);
}
void	ft_free_list(t_global *global)
{
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_lst_clear3(&global->head_env, free);
	// ft_free_tab(global->sorted_env);
	ft_free_tab(global->env);
}

void	ft_close(t_global *global)
{
	t_cmd *cmd;

	cmd = global->headcmd;
	while (cmd)
	{
		if (cmd->pipe)
		{
			close(cmd->fd_pipe[0]);
			close(cmd->fd_pipe[1]);
		}
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	char *line;
	t_global	global;
	(void)ac;
	(void)av;
	g_exit_status = 0;
	ft_init_minishell(&global, envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (!global.exit)
	{
		line = readline("\033[01;32m ​💥​ Minishell Happiness ​💥​ ➜ \e[00m");
		if (!line)
		{
			printf("exit\n");
			global.exit = true;
			ft_free_list(&global);
			exit(0);
		}
		add_history(line);
		ft_signal(0);
		init_line(line, &global.head);
		if (!analize_cmd(&global.head, &global.headcmd))
		{
			if (!last_call_quotes(global.headcmd, global.head))
				parse_execution(&global);
			else
			{
				ft_close(&global);
				ft_lst_clear(&global.head, free);
				ft_lst_clear2(&global.headcmd, free);
			}
		}
		else
		{
			ft_close(&global);
			ft_lst_clear(&global.head, free);
			ft_lst_clear2(&global.headcmd, free);
		}
		free(line);
	}
	ft_close(&global);
	ft_free_list(&global);
	exit(g_exit_status);
}
