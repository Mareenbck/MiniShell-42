/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:26:07 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/11 16:58:40 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char *line;
	t_global	global;
	(void)ac;
	(void)av;

	global.head = NULL;
	global.headcmd = NULL;
	global.head_env = NULL;
	ft_init_env(&global, envp);
	ft_init_list_env(&global.head_env, envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("\033[01;32m ​💥​ Minishell Happiness ​💥​ ➜ \e[00m");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line && ft_strncmp(line, "exit", 4) == 0)
			break ;
		add_history(line);
		init_line(line, &global.head);
		analize_cmd(&global.head, &global.headcmd);
		//parse_final_quotes(global.head);
		parso(global.head);
		ft_signal(0);
		ft_execution(&global);
	}
}
