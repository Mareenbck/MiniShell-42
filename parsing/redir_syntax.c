/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:55:28 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/24 16:04:15 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir_o_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		return (1);
	if (token->prev == NULL)
		return (1);
	return (0);
}

int	check_redir_i_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		return (1);
	if (token->prev == NULL)
		return (1);
	return (0);
}

int check_append_o(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		return (1);
	if (token->prev == NULL)
		return (1);
	return (0);
}

int check_heredoc(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		return (1);
	return (0);
}

// void	analize_redir(t_token *token, t_cmd *cmd)
// {
// 	if (token->token == REDIR_OUT)
// 	{
// 		check_redir_o_position(token, cmd);
// 		redir_out(cmd, token->next->val);
// 	}
// 	if (token->token == REDIR_IN)
// 	{
// 		//check_redir_i_position(token, cmd);
// 		redir_in(cmd, token->prev->val);
// 	}
// }
