/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:45:54 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/08 16:23:35 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_name(char *token)
{
	int	i;

	i = 0;
	if (ft_isdigit(token[i]))
	{
		printf("not a valid identifier\n");
		return (1);
	}
	while (token[i] != '=' && token[i] != '\0')
	{
		if (!ft_isalnum(token[i]) && !ft_strchr("_+=", token[i]))
		{
			printf("not a valid identifier\n");
			return (1);
		}
		i++;
	}
	return (0);
}

char	*check_value(char *token)
{
	char	*value;
	char	*tmp;

	value = ft_strchr(token, '=');
	if (!value)
		return (ft_strdup(""));
	else
		value = ft_strdup(&value[1]);
	if (value[0] == '\"' || value[0] == '\'')
	{
		tmp = ft_strtrim(value, "\"\'");
		free(value);
		return (tmp);
	}
	return (value);
}
