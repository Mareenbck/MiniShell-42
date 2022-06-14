/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 08:57:01 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/14 12:11:53 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_global *global)
{
	// char	*path;
	t_env	*env;
	env = find_name(&global->head_env, "PWD", 3);
	if (env)
		printf("%s\n", env->var_value);
	// path = getcwd(NULL, 0);
	// if (!path)
	// 	return (1);
	// printf("%s\n", path);
	// free(path);
	return (0);
}
