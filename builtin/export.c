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

//FAIRE UEN STRUCT TMP POUR ENREGISTRER NOM ET SIGNE FORMATE
int	ft_export(t_token *token, t_env **head_env)
{
	t_env *env;
	t_env *new_env;
	char *value;
	char *sign;

	env = NULL;
	if (token->val == NULL)
		ft_print_export(head_env);
	while (token->next != NULL && token->token == WORD)
	{
		value = check_value(token->val);
		if (!check_name(token->val, token->expand))
		{
			sign = init_sign(token->val);
			env = find_name(head_env, edit_name(token->val, '='));
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
				new_env = create_var_env(edit_name(token->val, '='), value, sign);
				ft_lst_insert(head_env, new_env);
			}
		}
		token = token->next;
	}
	// ft_print_env(head_env);
	return (0);
}
