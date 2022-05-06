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
		if (*tmp->var_value == '\0' && *tmp->var_sign == '\0')
			printf("%s %s%s\n", tmp->declare, tmp->var_name, tmp->var_sign);
		else
			printf("%s %s%s\"%s\"\n", tmp->declare, tmp->var_name, tmp->var_sign, tmp->var_value);
		tmp = tmp->next;
	}
}

// A FINIR
int check_name(char *name)
{
	int i;

	i = 0;
	if (ft_isdigit(name[i]))
		printf("wrong arg\n");
	while (ft_isalnum(name[i]) || name[i] == '_')
		i++;
	return (0);
}

char *check_value(char *value)
{
	// int i;

	// i = 0;
	value = ft_strtrim(&value[0], "=");
	// while (ft_isalnum(name[i]) || name[i] == '_')
	// 	i++;
	// if (name[i] == '+' && name[i+1] == '=')
	// {
	// 	env = find_name(head_env, name);
	// 	value = ft_strjoin(env->var_value, value);
	// 	free(env->var_value);
	// }
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
	char *sign;

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
			check_name(name);
			sign = init_sign(name);
			name = edit_name(name, '=');
			env = find_name(head_env, name);
			if (env != NULL)
			{
				if (sign[0] == '+')
					env->var_value = ft_strjoin(env->var_value, value);
				else
					env->var_value = value;
			}
			else
			{
				new_env = create_var_env(name, value, sign);
				ft_lst_insert(head_env, new_env);
			}
		}
		token = token->next;
	}
	// ft_print_env(head_env);
}
