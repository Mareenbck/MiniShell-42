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

#include "minishell.h"

// int	ft_cd(t_token *token, t_data *data)
// {
// 	char	*new_path;
// 	char	*old_path;
// 	int	ret;

// 	new_path = NULL;
// 	old_path = NULL;
// 	ret = 0;
// 	if (token->next && token->next->next)
// 	{
// 		printf("cd: too many arguments\n");
// 		return (1);
// 	}
// 	old_path = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
// 	browse_data_var(old_path, data);
// 	if (token->next)
// 		ret = chdir(token->next->data);
// 	else
// 		ret = chdir(getenv("HOME"));
// 	if (ret == -1)
// 	{
// 		printf("cd: %s: No such file or directory\n", token->next->data);
// 		return (1);
// 	}
// 	new_path = ft_strjoin("PWD=", getcwd(NULL, 0));
// 	browse_data_var(new_path, data);
// 	return (0);
// }

int	browse_data_var(char *str, t_global *global)
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
			// free(global->env[i]);
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
	// (void)str;

	arg = ft_split(str, ' ');
	i = 0;
	while (arg[i] != NULL)
	{
		// printf("arg[%d] %s\n", i, arg[i]);
		i++;
	}
	// arg[i] = NULL;
	// printf("arg[%d] %s\n", i, arg[i]);

	if (i > 2)
		ft_error("cd : too many arguments\n");
	// printf("lol");
	old_path = ft_strjoin("OLDPWD=", getcwd(NULL,0));
	printf("old path %s\n", old_path);
	browse_data_var(old_path, global);
	if (arg[1])
	{
		new = ft_strjoin(getcwd(NULL,0), arg[1]);
		chdir(new);
	}
	// else
	// 	chdir("HOME");
	new_path = ft_strjoin("PATH=", getcwd(NULL,0));
	printf("new path %s\n", new_path);
	browse_data_var(new_path, global);
	// chdir("/mnt/nfs/homes/mbascuna/github/minishell/test/");
}
