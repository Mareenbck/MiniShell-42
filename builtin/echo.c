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
	while (token != NULL)
	{
		if (token->val == NULL)
			printf(" ");
		else if (!ft_strncmp(token->val, "-n", 2))
			option = 1;
		else if (token->next != NULL)
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
