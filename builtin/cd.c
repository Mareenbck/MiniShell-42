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
	t_env *oldpwd;
	t_env *newpwd;
	t_env *home;

	if (cmd->val[2] != NULL)
		printf("cd : too many arguments\n");
	oldpwd = find_name(&global->head_env, "OLDPWD", 6);
	if (oldpwd != NULL)
		oldpwd->var_value = getcwd(NULL, 0);
	if (cmd->val[1] == NULL || !ft_strncmp(cmd->val[1], "~", 2) || !ft_strncmp(cmd->val[1], "/", 2))
	{
		// DOIT RETOURNER A HOME OU RACINE DU MINISHELL ??
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
	newpwd = find_name(&global->head_env, "PWD", 4);
	if (newpwd != NULL)
		newpwd->var_value = getcwd(NULL, 0);
	return (0);
}
