/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:54:00 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/10 10:25:01 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_free_list_return(t_global *global)
{
	ft_lst_clear3(&global->head_env, free);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_free_tab(global->env);
	return (1);
}

int	ft_free_list_and_error(t_global *global, t_cmd *cmd)
{
	t_env	*env;

	env = find_name(&global->head_env,
			&cmd->val[0][1], ft_strlen(&cmd->val[0][1]));
	if (env)
		printf("%s : command not found\n", env->var_value);
	else
		perror("Command Not Found");
	ft_lst_clear3(&global->head_env, free);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_free_tab(global->env);
	return (1);
}
