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

char	*ft_change_oldpwd(t_global *global)
{
	t_env	*env = NULL;
	char	*path = NULL;
	char	*oldpwd = NULL;

	env = find_name(&global->head_env, "OLDPWD", 6);
	if (env)
	{
		oldpwd = ft_strdup(env->var_value);
		free(env->var_value);
		path = getcwd(NULL, 0);
		if (!path)
			return (NULL);
		env->var_value = ft_strdup(path);
		free(path);
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

void	ft_go_new_path(t_cmd *cmd)
{
	char	*new;

	new = ft_strjoin(getcwd(NULL, 0), "/");
	new = ft_strjoin(new, cmd->val[1]);
	if (!new || chdir(new) == -1)
		printf("bash: cd: No such file or directory\n");
	free(new);
}

void	ft_save_new_pwd(t_global *global)
{
	t_env	*env;
	char	*path;

	env = find_name(&global->head_env, "PWD", 3);
	if (env)
	{
		free(env->var_value);
		path = getcwd(NULL, 0);
		if (!path)
			return ;
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
		chdir(oldpwd);
	else
		ft_go_new_path(cmd);
	ft_save_new_pwd(global);
	free(oldpwd);
	ft_init_list_env(&global->head_env, global);
	return (0);
}
