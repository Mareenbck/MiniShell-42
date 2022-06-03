/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:45:51 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/01 15:41:59 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_env(t_global *global, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	global->env = (char **)malloc(sizeof(t_env) * i + 1);
	if(!global->env)
		ft_error("Error\n", ALLOCATION_FAIL);
	i = 0;
	while (envp[i])
	{
		global->env[i] = ft_strdup(envp[i]);
		i++;
	}
	global->env[i] = NULL;
	// ft_init_sorted_env(global);
}

void	ft_init_sorted_env(t_global *global)
{
	int	i;

	i = 0;
	while (global->env[i])
		i++;
	global->sorted_env = (char **)malloc(sizeof(t_env) * i + 1);
	if(!global->sorted_env)
		ft_error("Error\n", ALLOCATION_FAIL);
	i = 0;
	while (global->env[i])
	{
		global->sorted_env[i] = global->env[i];
		i++;
	}
	global->sorted_env[i] = NULL;
	ft_sort_tab(global->sorted_env);
}

// POUR TEST__ A VIRER PLUS TARD
void ft_print_env(t_env **head)
{
	t_env *tmp;

	tmp = *head;
	int i = 0;

	while (tmp != NULL)
	{
		printf("%d > name : %s  sign : %s value : %s \n", i, tmp->var_name, tmp->var_sign, tmp->var_value);
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
	new_var_env->var_sign = NULL;
	new_var_env->next = NULL;
	new_var_env->prev = NULL;
	return (new_var_env);
}

t_env  *create_var_env(char *name, char *env)
{
	t_env *new_var_env;

	new_var_env = ft_init_var_env();
	new_var_env->declare = ft_strdup("declare -x");
	new_var_env->var_name = ft_strdup(name);
	new_var_env->var_value = check_value(env);
	new_var_env->var_sign = init_sign(env);
	new_var_env->next = NULL;
	new_var_env->prev = NULL;
	return (new_var_env);
}

char *edit_name(char *str, char c)
{
	int i;
	char *res;

	i = 0;
	while (str[i] != c)
	{
		i++;
		if (str[i] == '\0')
			return (str);
	}
	while (ft_strchr("=+", str[i]))
		i--;
	i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	res[i] = '\0';
	while (--i >= 0)
		res[i] = str[i];
	return (res);
}

char *init_sign(char *name)
{
	size_t i;
	size_t j;
	int size;
	char *res;

	i = 0;
	while (name[i] != '=' && name[i] != '\0')
		i++;
	j = i;
	if (name[j] == '=')
	{
		j--;
		if (name[j] == '+')
			j--;
	}
	res = (char *)malloc(sizeof(char) * (i - j + 1));
	if (!res)
		return (NULL);
	size = 0;
	while (j++ < i)
		res[size++] = name[j];
	res[size] = '\0';
	return (res);
}

void	ft_init_list_env(t_env **head_env, t_global *global)
{
	int	i;
	char *name;
	// char *value;
	// char *sign;
	t_env *new_var_env;

	// envp = ft_sort_tab(envp);
	i = 0;
	ft_init_sorted_env(global);
	while (global->sorted_env[i])
	{
		// value = check_value(global->sorted_env[i]);
		// sign = init_sign(global->sorted_env[i]);
		if (!check_name(global->sorted_env[i]))
			name = edit_name(global->sorted_env[i], '=');
		new_var_env = create_var_env(name, global->sorted_env[i]);
		free(name);
		ft_lstaddback3(head_env, new_var_env);
		i++;
	}
	ft_lstaddback3(head_env, ft_init_var_env());
	free(global->sorted_env);
	// ft_print_env(head_env);
}
