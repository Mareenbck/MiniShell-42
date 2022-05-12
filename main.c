/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:26:07 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/06 13:18:56 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_minishell(t_global *global, char **envp)
{
	global->head = NULL;
	global->headcmd = NULL;
	global->head_env = NULL;
	global->exit = false;
	ft_init_env(global, envp);
	ft_init_list_env(&global->head_env, global);
	// printf("COUCOU\n");
}

void	ft_free_list(t_global *global)
{
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_lst_clear3(&global->head_env, free);
	// ft_free_tab(global->sorted_env);
	ft_free_tab(global->env);
}

int	main(int ac, char **av, char **envp)
{
	char *line;
	t_global	global;
	(void)ac;
	(void)av;

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
		init_line(line, &global.head);
		analize_cmd(&global.head, &global.headcmd);
		// trim_doble_quotes(global.head);
		// trim_simple_quotes(global.head);
		ft_signal(0, &global);
		ft_execution(&global);
		free(line);
	}
	ft_free_list(&global);
	exit(global.exit_status);
}


