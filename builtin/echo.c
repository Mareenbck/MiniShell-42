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


int	ft_echo(t_token *token)
{
	if (ft_strncmp(token->val, "-n", 3) == 0)
		token = token->next;
	while (token)
	{
		printf("%s",token->val);
		token = token->next;
	}
	printf("\n");
	return (0);
}
