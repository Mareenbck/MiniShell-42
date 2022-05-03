/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:26:42 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/03 15:16:09 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	analise_pipe(t_token **head, t_cmd **comd)
// {
// 	t_token *token;
// 	t_cmd	*cmd;
// 	token = *head;

// 	while (token != NULL)
// 	{
// 		if (token->token == PIPE)
// 		{
// 			cmd = ft_init_cmd();
// 		}
// 		token = token->next;
// 	}
// }

int	check_pipe_position(t_token **head)
{
	t_token *token;

	token = *head;
	while (token != NULL)
	{
		while (token->token == PIPE)
		{
			if (token->next->val == NULL)
				return (1);
			if (token->next->token == PIPE)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

void check_global_pipe(t_token **head)
{
	if (!(check_pipe_position(head)))
		ft_error("syntax error\n");
}