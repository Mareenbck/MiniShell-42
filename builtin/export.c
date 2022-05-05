/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:18:49 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/04 11:19:02 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(t_env **head)
{
	t_env *tmp;

	tmp = *head;
	while (tmp->next != NULL )
	{
		if (*tmp->var_value == '\0' && !ft_strchr(tmp->var_name, '='))
			printf("%s %s\n", tmp->declare, tmp->var_name);
		else
			printf("%s %s\"%s\"\n", tmp->declare, tmp->var_name, tmp->var_value);
		tmp = tmp->next;
	}
}

// A FINIR
char *check_name(char *name, t_token *token, char *value, t_env *env, t_env **head_env)
{
	int i;

	i = 0;
	if (!name)
		name = token->val;
	else if (ft_isdigit(name[i]))
		return (NULL);
	while (ft_isalnum(name[i]) || name[i] == '_')
		i++;
	if (name[i] == '+' && name[i++] != '=')
	{
		name = ft_strtrim(&name[i], "+");
		env = find_name(head_env, name);
		if (env != NULL)
			ft_strcat(env->var_value, value);
	}
	return (name);
}

char *check_value(char *value)
{
	value = ft_strtrim(&value[0], "=");
	if (!value)
		value = "\0";
	else if (value[0] == '\"')
	{
		value = ft_strtrim(value, "\"");
		printf("value : %s\n", value);
	}
	else if (value[0] == '\'')
		value = ft_strtrim(value, "\'");
	return (value);
}

void	ft_export(t_token *token, t_env **head_env)
{
	t_env *env;
	t_env *new_env;
	char *value;
	char *name;

	env = NULL;
	if (token->val == NULL)
		ft_print_export(head_env);
	while (token->next != NULL)
	{
		if (token->token == WORD)
		{
			value = ft_strchr(token->val, '=');
			value = check_value(value);
			name = init_var_name(token->val, '=');
			name = check_name(name, token, value, env, head_env);
			env = find_name(head_env, name);
			if (env != NULL)
				env->var_value = value;
			else
			{
				new_env = create_var_env(name, value);
				ft_lst_insert(head_env, new_env);
			}
		}
		token = token->next;
	}
}
