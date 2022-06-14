/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:25:51 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/14 15:57:23 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_change_oldpwd(t_global *global)
{
	t_env	*env;
	t_env	*pwd;
	char	*oldpwd;

	env = find_name(&global->head_env, "OLDPWD", 6);
	if (env)
	{
		oldpwd = ft_strdup(env->var_value);
		pwd = find_name(&global->head_env, "PWD", 3);
		free(env->var_value);
		env->var_value = ft_strdup(pwd->var_value);
		ft_change_env(ft_strdup("OLDPWD"), env->var_value, global);
	}
	return (oldpwd);
}

void	ft_go_home(t_global *global)
{
	t_env	*home;

	home = find_name(&global->head_env, "HOME", 4);
	chdir(home->var_value);
}

int	ft_go_new_path(t_cmd *cmd, t_global *global)
{
	char	*new;
	char	*tmp;
	t_env	*pwd;

	pwd = find_name(&global->head_env, "PWD", 3);
	if (!pwd)
	{
		printf("bash: cd: No such file or directory\n");
		return (1);
	}
	tmp = ft_strdup(pwd->var_value);
	new = ft_strjoin(tmp, "/");
	new = ft_strjoin(new, cmd->val[1]);
	if (chdir(new) == -1)
		printf("bash: cd1: No such file or directory\n");
	free(new);
	return (0);
}

void	ft_save_new_pwd(t_global *global)
{
	t_env	*env;
	char	*path;

	env = find_name(&global->head_env, "PWD", 3);
	if (env)
	{
		path = getcwd(NULL, 0);
		if (!path)
			return ;
		free(env->var_value);
		env->var_value = ft_strdup(path);
		free(path);
		ft_change_env(ft_strdup("PWD"), env->var_value, global);
	}
}

int	ft_cd(t_cmd *cmd, t_global *global)
{
	char	*oldpwd;

	if (cmd->val[2] != NULL)
	{
		printf("cd : too many arguments\n");
		return (1);
	}
	oldpwd = ft_change_oldpwd(global);
	if (cmd->val[1] == NULL || !ft_strncmp(cmd->val[1], "~", 2)
		|| !ft_strncmp(cmd->val[1], "/", 2))
		ft_go_home(global);
	else if (!ft_strncmp(cmd->val[1], "-", 2))
	{
		if (chdir(oldpwd) == -1)
			printf("bash: cd: No such file or directory\n");
	}
	else
		ft_go_new_path(cmd, global);
	ft_save_new_pwd(global);
	ft_init_list_env(&global->head_env, global);
	free(oldpwd);
	return (0);
}
