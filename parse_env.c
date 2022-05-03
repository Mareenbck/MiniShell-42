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


char	*search_envp(t_env **head_env, char *str)
{
	char	*path;
	t_env *env;

	env = *head_env;
	while (env->next != NULL)
	{
		path = ft_strnstr(env->env, str, ft_strlen(str));
		if (path)
		{
			path = ft_substr(env->env, 5, ft_strlen(env->env));
			if (!path)
				ft_error("Error");
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

char	**ft_split_envp(t_env **head_env)
{
	char	*paths;
	char	**split_path;

	paths = search_envp(head_env, "PATH=");
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
			exit(1);
		if (access(join_path, F_OK) == 0)
			return (join_path);
		i++;
	}
	return (NULL);
}

