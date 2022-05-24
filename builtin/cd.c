/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:25:51 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/27 09:26:01 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_cmd *cmd, t_global *global)
{
	char *new;
	t_env *env;
	// t_env *newpwd;
	t_env *home;
	char *path;
	// t_env *old;

	// env = global->head_env;
	if (cmd->val[2] != NULL)
	{
		printf("cd : too many arguments\n");
		return (1);
	}
	env = find_name(&global->head_env, "OLDPWD", 6);
	if (env)
	{
		free(env->var_value);
		path = getcwd(NULL, 0);
		env->var_value = ft_strdup(path);
		free(path);
		//printf("VAR NAME : %s, VALUE : %s\n", env->var_name, env->var_value);
		ft_change_env(ft_strdup("OLDPWD"), env->var_value, global);
	//	printf("%s\n", env->var_value);
	}
	if (cmd->val[1] == NULL || !ft_strncmp(cmd->val[1], "~", 2) || !ft_strncmp(cmd->val[1], "/", 1))
	{
		home = find_name(&global->head_env, "HOME", 4);
		chdir(home->var_value);
	}
	else
	{
		new = ft_strjoin(getcwd(NULL,0), "/");
		new = ft_strjoin(new, cmd->val[1]);
		if (chdir(new) == -1)
			printf("bash: cd: No such file or directory\n");
		free(new);
	}
	env = find_name(&global->head_env, "PWD", 3);
	if (env)
	{
		free(env->var_value);
		path = getcwd(NULL, 0);
		env->var_value = ft_strdup(path);
		free(path);
		// env->var_value = ft_strdup(getcwd(NULL, 0));
		ft_change_env(ft_strdup("PWD"), env->var_value, global);
	}
	ft_init_list_env(&global->head_env, global);
	return (0);
}
