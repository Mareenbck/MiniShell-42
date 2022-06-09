/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:45:51 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/09 12:56:41 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_init_var_env(void)
{
	t_env	*new_var_env;

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

void	ft_init_env(t_global *global, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	global->env = (char **)malloc(sizeof(t_env) * i + 1);
	if (!global->env)
		perror("Error\n");
	i = 0;
	while (envp[i])
	{
		global->env[i] = ft_strdup(envp[i]);
		i++;
	}
	global->env[i] = NULL;
}

void	ft_init_sorted_env(t_global *global)
{
	int	i;

	i = 0;
	while (global->env[i])
		i++;
	global->sorted_env = (char **)malloc(sizeof(t_env) * i + 1);
	if (!global->sorted_env)
		perror("Error\n");
	i = 0;
	while (global->env[i])
	{
		global->sorted_env[i] = global->env[i];
		i++;
	}
	global->sorted_env[i] = NULL;
	ft_sort_tab(global->sorted_env);
}

void	ft_print_env(t_env **head)
{
	t_env	*tmp;
	int		i;

	tmp = *head;
	i = 0;
	while (tmp != NULL)
	{
		printf("%d > name : %s  sign : %s value : %s \n",
			i, tmp->var_name, tmp->var_sign, tmp->var_value);
		i++;
		tmp = tmp->next;
	}
}

void	ft_init_list_env(t_env **head_env, t_global *global)
{
	int		i;
	char	*name;
	char	*sign;
	t_env	*new_var_env;

	i = 0;
	ft_init_sorted_env(global);
	while (global->sorted_env[i])
	{
		sign = init_sign(global->sorted_env[i]);
		if (!check_name(global->sorted_env[i]))
			name = edit_name(global->sorted_env[i], '=');
		new_var_env = create_var_env(name, global->sorted_env[i], sign);
		free(name);
		free(sign);
		ft_lstaddback3(head_env, new_var_env);
		i++;
	}
	ft_lstaddback3(head_env, ft_init_var_env());
	free(global->sorted_env);
}
