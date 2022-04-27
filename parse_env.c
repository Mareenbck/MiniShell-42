/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:55:02 by mbascuna          #+#    #+#             */
/*   Updated: 2022/01/13 14:49:33 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*search_envp(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]));
			if (!path)
				ft_error("Error");
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	**ft_split_envp(char **env)
{
	char	*paths;
	char	**split_path;

	paths = search_envp(env);
	split_path = ft_split(paths, ':');
	if (!split_path)
		ft_error("Split error");
	free(paths);
	return (split_path);
}

char	*ft_join_envp(char **split_path, char *av)
{
	int		i;
	char	*join_path;

	i = 0;
	while (split_path[i])
	{
		join_path = ft_strjoin(split_path[i], "/");
		join_path = ft_strjoin(join_path, av);
		if (!join_path)
			ft_error("Error");
		if (access(join_path, F_OK) == 0)
			return (join_path);
		i++;
	}
	return (NULL);
}

void	ft_exe(t_global *global, char *line)
{
	char	*cmd;
	char	**split_path;
	char	**cmd_args;

	cmd_args = ft_split(line, ' ');
	if (!cmd_args)
		ft_error("Split failed");
	split_path = ft_split_envp(global->env);
	cmd = ft_join_envp(split_path, cmd_args[0]);
	if (!cmd)
		ft_error("command not found");
	// ft_free_tab(split_path);
	if (execve(cmd, cmd_args, global->env) == -1)
	{
		ft_free_tab(cmd_args);
		ft_error("Error of execution");
	}
}
