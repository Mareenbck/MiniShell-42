/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:10:39 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/17 15:27:23 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	ft_init_minishell(t_global *global, char **envp)
{
	g_exit_status = 0;
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
	if (!global->head->next)
	{
		ft_lst_clear(&global->head, free);
		return (1);
	}
	if (analize_cmd(&global->headcmd, global) == 1)
	{
		ft_lst_clear(&global->head, free);
		ft_lst_clear2(&global->headcmd, free);
		return (1);
	}
	return (0);
}

int	ft_check_arg(int ac)
{
	if (ac != 1)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	return (0);
}

char	*ft_prompt(char *line, t_global *global)
{
	ft_signal(2);
	line = readline("\033[01;32m 💥\2 Minishell Happiness \1💥 ➜ \e[00m");
	ft_signal(0);
	if (!line)
		ft_quit(global);
	add_history(line);
	return (line);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_global	global;

	(void)av;
	if (ft_check_arg(ac))
		return (1);
	ft_init_minishell(&global, envp);
	while (global.exit != 1)
	{
		line = ft_prompt(line, &global);
		if (!init_token_cmd_list(line, &global))
		{
			if (!last_call_quotes(&global))
			{
				ft_expand_cmd_first(&global);
				ft_parse_execution(&global);
			}
		}
		free(line);
	}
	return (ft_quit_minishell(&global));
}
