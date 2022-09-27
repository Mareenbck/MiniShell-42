/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 08:57:01 by mbascuna          #+#    #+#             */
/*   Updated: 2022/09/27 09:51:33 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_global *global, t_cmd *cmd)
{
	t_env	*env;

	env = find_name(&global->head_env, "PWD", 3);
	if (env)
	{
		char *value = env->var_value;
		write(cmd->output, value, ft_strlen(value));
		write(cmd->output, "\n", 1);

	}
	return (0);
}
