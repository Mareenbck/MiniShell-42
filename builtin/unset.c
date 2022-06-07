/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:04:52 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/07 18:55:39 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_valid(char *str)
{
	int	i;

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

void	ft_unset_bis(t_global *global, int i)
{
	while (global->env[i] && global->env[i + 1])
	{
		free(global->env[i]);
		global->env[i] = ft_strdup(global->env[i + 1]);
		i++;
	}
	free(global->env[i]);
	global->env[i] = NULL;
}

int	ft_unset(t_cmd *cmd, t_global *global)
{
	int		i;
	char	*name;
	t_token	*token;

	i = -1;
	token = global->head->next;
	while (token->next != NULL)
	{
		if (!not_valid(token->val))
		{
			printf("unset: not a valid identifier\n");
			return (1);
		}
		token = token->next;
	}
	while (global->env[++i])
	{
		name = edit_name(global->env[i], '=');
		if (ft_strcmp(name, cmd->val[1]) == 0)
			ft_unset_bis(global, i);
		free(name);
	}
	ft_lst_clear3(&global->head_env, free);
	ft_init_list_env(&global->head_env, global);
	return (0);
}
