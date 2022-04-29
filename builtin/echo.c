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
int	ft_echo(t_token *token)
{
	int option;

	option = 0;
	if (token->val == NULL)
		printf(" ");
	else if (!ft_strncmp(token->val, "-", 1) && !ft_strncmp(token->next->val, "n", 1))
	{
		option = 1;
		token = token->next->next;
	}
	else if (token->next != NULL)
	{
		while (token->next != NULL)
		{
			printf("%s",token->val);
			token = token->next;
		}
	}
	if (!option)
		printf("\n");
	return (0);
}
