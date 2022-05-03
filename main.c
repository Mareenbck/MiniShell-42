/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:26:07 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/03 14:50:13 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void ft_print_env(t_env **head)
{
	t_env *tmp;

	tmp = *head;
	int i = 0;

	while (tmp != NULL)
	{
		printf("%d > env : %s \n", i, tmp->env);
		i++;
		tmp = tmp->next;
	}
}

t_env *ft_init_var_env()
{
  t_env *new_var_env;

  new_var_env = malloc(sizeof(t_env));
  if (!new_var_env)
    return (NULL);
  new_var_env->env = NULL;
  new_var_env->next = NULL;
  new_var_env->prev = NULL;
  return (new_var_env);
}

t_env  *create_var_env(char *envp)
{
  t_env *new_var_env;

  new_var_env = ft_init_var_env();
  new_var_env->env = ft_strdup(envp);
  new_var_env->next = NULL;
  new_var_env->prev = NULL;
  return (new_var_env);
}

void	ft_init_list_env(t_env **head_env, char **envp)
{
	int	i;
	t_env *new_var_env;

	i = 0;
	while (envp[i])
	{
		new_var_env = create_var_env(envp[i]);
		ft_lstaddback3(head_env, new_var_env);
		i++;
	}
	ft_lstaddback3(head_env, ft_init_var_env());
	// ft_print_env(head_env);
}

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
		// check_global_pipe(&global.head);
		ft_signal(0);
		ft_execution(&global);
	}
}
