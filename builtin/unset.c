/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:04:52 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/09 11:05:06 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_valid(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '=')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_unset(t_cmd *cmd, t_global *global)
{
	int i;
	char *name;
	t_token *token;

	i = -1;
	token = global->head->next;
	while (global->env[++i])
	{
		name = edit_name(global->env[i], '=');
		if (!not_valid(token->val))
		{
			printf("unset: not a valid identifier\n");
			break ;
		}
		if (ft_strcmp(name, cmd->val[1]) == 0)
		{
			free(name);
			while (global->env[i] && global->env[i + 1])
			{
				free(global->env[i]);
				global->env[i] = ft_strdup(global->env[i + 1]);
				i++;
			}
			// free(global->env[i]);
			global->env[i] = NULL;
		}
	}
	ft_lst_clear3(&global->head_env, free);
	// ft_free_tab(global->env);
	// free(global->sorted_env);
	// ft_free_tab(global->env);
	ft_init_list_env(&global->head_env, global);
	return (0);
}
