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

int	ft_unset(t_token *token, t_global *global)
{
	int i;
	char *name;

	i = -1;
	while (global->env[++i])
	{
		name = edit_name(global->env[i], '=');
		printf("name : %s\n", name);
		if (!ft_strncmp(name, token->val, (ft_strlen(token->val) + 1)))
		{
			while (global->env[i] && global->env[i + 1])
			{
				global->env[i] = ft_strdup(global->env[i + 1]);
				i++;
			}
			free(global->env[i]);
			global->env[i] = NULL;
		}
		i++;
	}
	ft_init_list_env(&global->head_env, global->env);
	return (0);
}
