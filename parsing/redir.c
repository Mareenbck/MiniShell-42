/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:53:14 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/17 16:32:15 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir_o_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		ft_error("error syntax 2\n", ERROR);
	if (token->prev == NULL)
		ft_error("error syntax \n", ERROR);
	return (0);
}

int	check_redir_i_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		ft_error("error syntax 2\n", ERROR);
	if (token->prev == NULL)
		ft_error("error syntax \n", ERROR);
	return (0);
}

int check_append_o(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		ft_error("syntax error2 \n", ERROR);
	if (token->prev == NULL)
		ft_error("syntax error \n", ERROR);
	return (0);
}

int check_append_i(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		ft_error("syntax error2 \n", ERROR);
	if (token->prev == NULL)
		ft_error("syntax error \n", ERROR);
	return (0);
}

void	create_file(t_token *token, int type)
{
	while (token->next != NULL)
	{
		if (token->token == REDIR_OUT)
		{
			if (type == 0)
				token->redir_out = open(token->out, O_CREAT, 00700);
			else if (type == 1)
				token->redir_out = open(token->out, O_APPEND, 00700);
		}
		token = token->next;
	}
}
