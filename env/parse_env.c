/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:55:02 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/17 13:05:57 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_name(t_env **head_env, char *var, size_t len)
{
	t_env *env;

	env = *head_env;
	while (env->next != NULL)
	{
		if (!ft_strncmp(env->var_name, var, len))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	**ft_split_envp(t_env **head_env, char *str)
{
	char	**split_path;
	t_env	*env;

	env = find_name(head_env, str, ft_strlen(str));
	if (env != NULL)
	{
		split_path = ft_split(env->var_value, ':');
		if (!split_path)
		{
			// ft_free_tab(split_path);
			ft_error("Error\n",ALLOCATION_FAIL);
		}
		return (split_path);
	}
	return (NULL);
}

char *find_binary(char **split_path, char *av)
{
	int		i;
	char	*join_path;
	char	*tmp;

	i = 0;
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		join_path = ft_strjoin(tmp, av);
		if (access(join_path, F_OK) == 0)
			return (join_path);
		i++;
	}
	return (NULL);
}

