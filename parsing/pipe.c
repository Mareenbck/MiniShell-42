/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:26:42 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/14 11:37:57 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next == NULL)
	{
		printf("OUI\n");
		return (1);
	}
	if (token->prev == NULL)
	{
		printf("OUI2\n");
		return (1);
	}
	return (0);
}
