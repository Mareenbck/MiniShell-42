/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:33:53 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/24 11:14:25 by emcariot         ###   ########.fr       */
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

int init_token_cmd_list(char *line, t_global *global)
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

void	ft_quit(t_global *global)
{
	printf("exit\n");
	global->exit = true;
	ft_free_list(global);
	exit(0);
}

int	main(int ac, char **av, char **envp)
{
	char *line;
	t_global	global;
	(void)ac;
	(void)av;
	g_exit_status = 0;
	ft_init_minishell(&global, envp);
	while (!global.exit)
	{
		ft_signal(2);
		// line = readline("\1\033[01;32m ​💥\2​ Minishell Happiness ​\1💥​ ➜ \e[00m\2");
		line = readline("\033[01;32m ​💥​ Minishell Happiness ​💥​ ➜ \e[00m");
		ft_signal(0);
		if (!line)
			ft_quit(&global);
		add_history(line);
		if (!init_token_cmd_list(line, &global))
		{
			if (!last_call_quotes(global.headcmd, global.head, &global))
			{
				ft_print_cmd(&global.headcmd);
				ft_expand_cmd_first(&global);
				parse_execution(&global);
			}
		}
		free(line);
	}
	// ft_close(&global);
	ft_free_list(&global);
	exit(g_exit_status);
}
