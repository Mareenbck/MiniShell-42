/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:34:42 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/29 09:34:55 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//RASSEMBLER - ET N DANS MEME TOKEN
int	ft_echo(t_token *token, t_env **head_env)
{
	int option;
	t_env *env;

	env = *head_env;
	option = 0;
	while (token != NULL)
	{
		if (token->expand)
		{
			env = find_name(head_env, edit_name(token->val, '='));
			printf("%s",env->var_value);
		}
		if (token->val == NULL)
			printf(" ");
		else if (!ft_strncmp(token->val, "-n", 2))
			option = 1;
		else if (token->next != NULL && !token->expand)
		{
			printf("%s",token->val);
			if (token->next->next != NULL)
				printf(" ");
		}
		token = token->next;
	}
	if (!option)
		printf("\n");
	return (0);
}
