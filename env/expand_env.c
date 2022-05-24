/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:45:54 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/09 13:46:07 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_name(char *token)
{
	int i;

	i = 0;
	if (ft_isdigit(token[i]))
		return (ft_wrong("Wrong args"));
	while (token[i] != '=' && token[i] != '\0')
	{
		if (!ft_isalnum(token[i]) && !ft_strchr("_+=", token[i]))
			return (ft_wrong("Wrong args"));
		i++;
	}
	return (0);
}

//Trim ttes les quotes mais l'affichage est gere avec le signe.
//si sign est = alors on entoure la value de quotes
char *check_value(char *token)
{
	char *value;

	value = ft_strchr(token, '=');
	if (!value)
		return(ft_strdup(""));
	else
		value = ft_strtrim(value, "=");
	if (value[0] == '\"')
		value = ft_strtrim(value, "\"");
	else if (value[0] == '\'')
		value = ft_strtrim(value, "\'");
	return (value);
}

