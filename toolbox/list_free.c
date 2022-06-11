/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:39:48 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/09 10:10:24 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_delone(t_token *token, void (*del)(void *))
{
	if (!del || !token)
		return ;
	if (token)
	{
		free(token->val);
		(*del)(token);
	}
}

void	ft_lst_delone2(t_cmd *cmd, void (*del)(void *))
{
	if (!del || !cmd)
		return ;
	if (cmd)
	{
		free(cmd->expand);
		free(cmd->path);
		(*del)(cmd);
	}
}

void	ft_lst_delone3(t_env *env, void (*del)(void *))
{
	if (!del || !env)
		return ;
	if (env)
	{
		free(env->declare);
		free(env->var_name);
		free(env->var_value);
		free(env->var_sign);
		(*del)(env);
	}
}

void	ft_free_list(t_global *global)
{
	ft_lst_clear3(&global->head_env, free);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_free_tab(global->env);
}

void	ft_free_list2(t_global *global)
{
	ft_lst_clear3(&global->head_env, free);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
}
