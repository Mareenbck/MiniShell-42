/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:29:39 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/09 11:29:56 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	ft_init_minishell(t_global *global, char **envp)
{
	global->head = NULL;
	global->headcmd = NULL;
	global->head_env = NULL;
	global->exit = false;
	ft_init_env(global, envp);
	ft_init_list_env(&global->head_env, global);
}

int	init_token_cmd_list(char *line, t_global *global)
{
	init_token_list(line, &global->head);
	if (!analize_cmd(&global->headcmd, global))
		return (0);
	else
	{
		ft_lst_clear(&global->head, free);
		ft_lst_clear2(&global->headcmd, free);
		return (1);
	}
}

void	go_exec(t_global global)
{
	ft_close(&global);
	ft_free_list(&global);
}

int ft_check_arg(int ac)
{
	if (ac != 1)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_global	global;

	(void)av;
	if (ft_check_arg(ac))
		return (1);
	ft_init_minishell(&global, envp);
	g_exit_status = 0;
	while (global.exit != 1)
	{
		ft_signal(2);
		line = readline("\1\033[01;32m ​💥\2​ Minishell Happiness ​\1💥​ ➜ \e[00m\2");
		ft_signal(0);
		if (!line)
			ft_quit(&global);
		add_history(line);
		if (!init_token_cmd_list(line, &global))
		{
			if (!last_call_quotes(global.headcmd, global.head, &global))
			{
				ft_expand_cmd_first(&global);
				ft_parse_execution(&global);
			}
		}
		free(line);
	}
	ft_close(&global);
	ft_free_list(&global);
	exit(g_exit_status);
}
