/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:26:07 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/20 16:37:36 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int			run(char **args, char *bin, int pipe)
// {
// 	if (!pipe)
// 		g_pid = fork();
// 	if (!pipe && g_pid < 0)
// 	{
// 		free(bin);
// 		ft_putstr_fd("minishell: execve: failed to create a new process.\n", 2);
// 		g_status = 1;
// 		return (-1);
// 	}
// 	else if (!g_pid)
// 		execve(bin, args, g_envs);
// 	free(bin);
// 	if (pipe)
// 		return (1);
// 	if (ft_strequ(args[0], "./minishell"))
// 		signal(SIGINT, SIG_IGN);
// 	wait(&g_pid);
// 	status_child();
// 	g_pid = 0;
// 	return (1);
// }

//COUCOU


void	ft_init_env(t_global *global, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	global->env = (char **)malloc(sizeof(char *) * i + 1);
	if(!global->env)
		ft_error("Error\n");
	i = 0;
	while (envp[i])
	{
		global->env[i] = ft_strdup(envp[i]);
		i++;
	}
	global->env[i] = NULL;
}

int	main(int ac, char **av, char **envp)
{
	char *line;
	t_global	global;
	(void)ac;
	(void)av;
	pid_t	pid;
	t_liste	*list;

	ft_init_env(&global, envp);
	if (signal(SIGINT, siginthandler) == SIG_ERR)
		write(1, "boobs", 6);
	if (signal(SIGQUIT,signalslash) == SIG_ERR)
		write(1, "marche pas", 11);
	while (1)
	{
		line = readline("> ");
		if (!line || line[0] == '\0')
			break ;
		if (line && ft_strncmp(line, "exit", 6) == 0)
			break ;
		add_history(line);
		ft_test_lex(line, &global);
		list = ft_split_pipe(line);
		afficherListe(list);
		pid = fork();
		if (pid == 0)
			ft_exe(&global, line);
		wait(&pid);
	}
}

