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

#include "../minishell.h"

t_env	*find_name(t_env **head_env, char *var)
{
	t_env *env;

	env = *head_env;
	while (env->next != NULL)
	{
		if (ft_strnstr(env->var_name, var, ft_strlen(var)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	**ft_split_envp(t_env **head_env)
{
	char	**split_path;
	t_env	*env;

	env = find_name(head_env, "PATH=");
	if (env != NULL)
	{
		split_path = ft_split(env->var_value, ':');
		printf("split_path :%s\n", split_path[0]);
		if (!split_path)
			ft_error("Split error");
		return (split_path);
	}
	return (NULL);
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

