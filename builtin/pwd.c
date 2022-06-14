/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 08:57:01 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/14 15:49:26 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_global *global)
{
	t_env	*env;

	env = find_name(&global->head_env, "PWD", 3);
	if (env)
		printf("%s\n", env->var_value);
	return (0);
}
