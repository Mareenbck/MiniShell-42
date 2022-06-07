/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:25:51 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/07 15:07:36 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_cmd *cmd, t_global *global)
{
	char *new;
	t_env *env;
	char *tmp;
	t_env *home;
	char *path;

	if (cmd->val[2] != NULL)
	{
		printf("cd : too many arguments\n");
		return (1);
	}
	env = find_name(&global->head_env, "OLDPWD", 6);
	if (env)
	{
		tmp = ft_strdup(env->var_value);
		free(env->var_value);
		path = getcwd(NULL, 0);
		env->var_value = ft_strdup(path);
		free(path);
		ft_change_env(ft_strdup("OLDPWD"), env->var_value, global);
	}
	if (cmd->val[1] == NULL || !ft_strncmp(cmd->val[1], "~", 2) || !ft_strncmp(cmd->val[1], "/", 2))
	{
		home = find_name(&global->head_env, "HOME", 4);
		chdir(home->var_value);
	}
	else if (!ft_strncmp(cmd->val[1], "-", 2))
	{
		chdir(tmp);
	}
	else
	{
		new = ft_strjoin(getcwd(NULL,0), "/");
		new = ft_strjoin(new, cmd->val[1]);
		if (chdir(new) == -1)
			printf("bash: cd: No such file or directory\n");
		free(new);
	}
	free(tmp);
	env = find_name(&global->head_env, "PWD", 3);
	if (env)
	{
		free(env->var_value);
		path = getcwd(NULL, 0);
		env->var_value = ft_strdup(path);
		free(path);
		ft_change_env(ft_strdup("PWD"), env->var_value, global);
	}
	ft_init_list_env(&global->head_env, global);
	return (0);
}
