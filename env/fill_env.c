/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:30:39 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/08 17:19:25 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_var_env(char *name, char *env)
{
	t_env	*new_var_env;

	new_var_env = ft_init_var_env();
	new_var_env->declare = ft_strdup("declare -x");
	new_var_env->var_name = ft_strdup(name);
	new_var_env->var_value = check_value(env);
	new_var_env->var_sign = init_sign(env);
	new_var_env->next = NULL;
	new_var_env->prev = NULL;
	return (new_var_env);
}

char	*fill_name(int i, char *str, char *res)
{
	res[i] = '\0';
	while (--i >= 0)
		res[i] = str[i];
	return (res);
}

char	*edit_name(char *str, char c)
{
	int		i;
	char	*res;

	i = 0;
	if (str[i] != c && str[i] != '+')
	{
		while (str[i] != c)
		{
			i++;
			if (str[i] == '\0')
			{
				res = ft_strdup(str);
				return (res);
			}
		}
		while (ft_strchr("=+", str[i]))
			i--;
		i++;
		res = (char *)malloc(sizeof(char) * (i + 1));
		if (!res)
			return (NULL);
		return (fill_name(i, str, res));
	}
	else
		return (NULL);
}

char	*fill_sign(int j, int i, char *name, char *res)
{
	int		size;

	size = 0;
	while (j++ < i)
		res[size++] = name[j];
	res[size] = '\0';
	return (res);
}

char	*init_sign(char *name)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	if (name[i] != '=')
	{
		while (name[i] != '=' && name[i] != '\0')
			i++;
		j = i;
		if (name[j] == '=')
		{
			j--;
			if (name[j] == '+')
				j--;
		}
		res = (char *)malloc(sizeof(char) * (i - j + 1));
		if (!res)
			return (NULL);
		return (fill_sign(j, i, name, res));
	}
	else
		return (NULL);
}
