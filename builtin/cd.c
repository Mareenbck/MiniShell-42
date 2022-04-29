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

int	replace_var_env(char *str, t_global *global)
{
	int	i;
	int	j;

	i = 0;
	while (global->env[i])
	{
		j = 0;
		while (str[j] == global->env[i][j] && str[j] != '=')
			j++;
		if (str[j] == '=')
		{
			free(global->env[i]);
			global->env[i] = ft_strdup(str);
			if (!global->env[i])
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}


void	ft_cd(char *str, t_global *global)
{
	char **arg;
	int i;
	char *new_path;
	char *old_path;
	char *new;
	char *home;
	// (void)str;

	arg = ft_split(str, ' ');
	i = 0;
	while (arg[i] != NULL)
		i++;
	if (i > 2)
		ft_error("cd : too many arguments\n");
	old_path = ft_strjoin("OLDPWD=", getcwd(NULL,0));
	printf("old path %s\n", old_path);
	replace_var_env(old_path, global);
	if (arg[1])
	{
		new = ft_strjoin(getcwd(NULL,0), arg[1]);
		chdir(new);
	}
	else if (!arg[1] || arg[1][0] == '~')
	{
		// DOIT RETOURNER A HOME OU RACINE DU MINISHELL ??
		home = search_envp(global->env, "HOME=");
		chdir(home);
	}
	new_path = ft_strjoin("PATH=", getcwd(NULL,0));
	printf("new path %s\n", new_path);
	replace_var_env(new_path, global);
}
