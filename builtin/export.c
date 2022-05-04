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
		printf("%s %s\"%s\" next > %s\n", tmp->declare, tmp->var_name, tmp->var_value, tmp->next->var_name);
		tmp = tmp->next;
	}
}

void	ft_export(t_token *token, t_env **head_env)
{
	// t_env *env;
	t_env *new_env;
	char *value;
	char *name;

	// env = *head_env;
	if (token->val == NULL)
		ft_print_export(head_env);
	while (token->next != NULL)
	{
		if (token->token == WORD)
		{
			value = ft_strchr(token->val, '=');
			name = init_var_name(token->val, '=');
			if (!name)
				name = token->val;
			// printf("name : %s, value : %s\n", name, &value[1]);
			new_env = create_var_env(name, &value[1]);
			// printf("new_env name: %s val:%s\n", new_env->var_name, new_env->var_value);
			ft_lst_insert(head_env, new_env);
			// ft_print_export(head_env);
		}
		token = token->next;
	}
}
