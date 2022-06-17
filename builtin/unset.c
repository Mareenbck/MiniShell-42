/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:04:52 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/17 15:22:39 by mbascuna         ###   ########.fr       */
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
		{
			printf("unset: not a valid identifier\n");
			return (0);
		}
	}
	return (1);
}

int	ft_check_args(t_global *global)
{
	t_token	*token;

	token = global->head->next;
	while (token->next != NULL)
	{
		if (!not_valid(token->val) || check_name(token->val))
			return (1);
		token = token->next;
	}
	return (0);
}

void	ft_shift_env(t_global *global, int i)
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

	i = -1;
	if (cmd->val[1] == NULL || ft_check_args(global))
	{
		g_exit_status = 1;
		return (1);
	}
	while (global->env[++i])
	{
		name = edit_name(global->env[i], '=');
		if (ft_strcmp(name, cmd->val[1]) == 0)
			ft_shift_env(global, i);
		free(name);
	}
	ft_lst_clear3(&global->head_env, free);
	ft_init_list_env(&global->head_env, global);
	return (0);
}
