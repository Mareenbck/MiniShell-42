/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:45:51 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/04 08:46:05 by mbascuna         ###   ########.fr       */
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
		printf("%d > name : %s  value : %s \n", i, tmp->var_name, tmp->var_value);
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
	new_var_env->declare = NULL;
	new_var_env->var_name = NULL;
	new_var_env->var_value = NULL;
	new_var_env->next = NULL;
	new_var_env->prev = NULL;
  return (new_var_env);
}

t_env  *create_var_env(char *envp, char *value)
{
	t_env *new_var_env;

	new_var_env = ft_init_var_env();
	new_var_env->declare = ft_strdup("declare -x");
	new_var_env->var_name = ft_strdup(envp);
	new_var_env->var_value = ft_strdup(value);
	new_var_env->next = NULL;
	new_var_env->prev = NULL;
	return (new_var_env);
}

char *init_var_name(char *str, char c)
{
	int i;
	char *res;

	i = 0;
	while (str[i] != c)
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	res[i++] = '\0';
	while (i-- >= 0)
		res[i] = str[i];
	return (res);
}

void	ft_init_list_env(t_env **head_env, char **envp)
{
	int	i;
	char *value;
	char *name;
	t_env *new_var_env;

	envp = ft_sort_tab(envp);
	i = 0;
	while (envp[i])
	{
		value = ft_strchr(envp[i], '=');
		name = init_var_name(envp[i], '=');
		new_var_env = create_var_env(name, &value[1]);
		ft_lstaddback3(head_env, new_var_env);
		i++;
	}
	ft_lstaddback3(head_env, ft_init_var_env());
	// ft_print_env(head_env);
}
