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
	t_env	*env;
	t_env *tmp;

	printf("token val : %s\n", token->val);
	env = find_name(&global->head_env, token->val);
	if (env)
	{
		tmp = (env)->next;
		ft_lst_delone3(env, free);
		env = tmp;
		printf("env name : %s, env value : %s\n",env->var_name, env->var_value);
	}
	return (0);
}
