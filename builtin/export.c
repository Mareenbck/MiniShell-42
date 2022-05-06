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
char *check_name(t_token *token)
{
	int i;
	char *name;

	i = 0;
	name = init_var_name(token->val, '=');
	if (!name)
		return (NULL);
	printf("name : %s", name);
	if (ft_isdigit(name[i]))
	{
		printf("wrong arg\n");
		return (NULL);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_' && name[i] != '=')
		{
			printf("Wrong : %c\n", name[i]);
			return (NULL);
		}
		i++;
	}
	return (name);
}

char *check_value(t_token *token)
{
	char *value;

	value = ft_strchr(token->val, '=');
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

//FAIRE UEN STRUCT TMP POUR ENREGISTRER NOM ET SIGNE FORMATE
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
	while (token->next != NULL && token->token == WORD)
	{
		value = check_value(token);
		name = check_name(token);
		if (name)
		{
			sign = init_sign(name);
			env = find_name(head_env, edit_name(name, '='));
			if (env)
			{
				if (sign[0] == '+')
					env->var_value = ft_strjoin(env->var_value, value);
				else
				{
					env->var_sign = sign;
					env->var_value = value;
				}
			}
			else
			{
				new_env = create_var_env(edit_name(name, '='), value, sign);
				ft_lst_insert(head_env, new_env);
			}
		}
		token = token->next;
	}
	// ft_print_env(head_env);
}
