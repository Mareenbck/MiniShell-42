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
		printf("%s %s\"%s\"\n", tmp->declare, tmp->var_name, tmp->var_value);
		tmp = tmp->next;
	}
}
// A FINIR
// int	name_is_valid(char *name)
// {
// 	int i;

// 	i = 0;
// 	if (ft_isdigit(str[i]))
// 		return (1);
// 	while (ft_isalnum(str[i]) || str[i] == '_')
// 		i++;
// 	if (str[i] == '+' && str[i++] != '=')
// 		return (1);
// 	return (0);
// }

void	ft_export(t_token *token, t_env **head_env)
{
	t_env *env;
	t_env *new_env;
	char *value;
	char *name;

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
			env = find_name(head_env, name);
			if (env != NULL)
				env->var_value = &value[1];
			else
			{
				new_env = create_var_env(name, &value[1]);
				ft_lst_insert(head_env, new_env);
				printf("name : %s\n", name);
			}
		}
		token = token->next;
	}
}
