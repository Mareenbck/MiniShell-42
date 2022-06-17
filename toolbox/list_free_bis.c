/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:54:00 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/17 12:12:44 by mbascuna         ###   ########.fr       */
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

	if (cmd->val[0][0] == '$')
	{
		env = find_name(&global->head_env,
				&cmd->val[0][1], ft_strlen(&cmd->val[0][1]));
		if (env && cmd->val[0][1])
			printf("%s : command not found\n", env->var_value);
		else
			perror("Command Not Found");
	}
	else
		perror("Command Not Found");
	ft_lst_clear3(&global->head_env, free);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_free_tab(global->env);
	return (1);
}

int	ft_free_list3(t_global *global)
{
	ft_lst_clear3(&global->head_env, free);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_free_tab(global->env);
	perror("Command Not Found");
	return (1);
}

int	check_lim(char *lim)
{
	int	i;

	i = -1;
	while (lim[++i])
		if (!ft_isalpha(lim[i]))
			return (1);
	return (0);
}
