/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:14:08 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/31 15:33:36 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_redir(t_token *token, t_cmd *cmd)
{
	if (token->token == REDIR_OUT)
	{
		if (check_redir_o_position(token, cmd) == 1)
		{
			return (1);
		}
		if (check_ambiguious_args(token->next->val, cmd))
		{
			ft_error("ambiguous redirect", 2);
			return (1);
		}
		else
			redir_out(cmd, token->next->val);
	}
	else if (token->token == REDIR_IN)
	{
		if (check_redir_i_position(token, cmd) == 1)
			return (1);
		if (check_access(cmd, token->next->val))
		{
			perror(token->next->val);
			return (1);
		}
	}
	return (0);
}

int	find_append(t_token *token, t_cmd *cmd)
{
	if (token->token == APPEND_OUT)
	{
		if (!check_append_o(token, cmd))
			append_out(cmd, token->next->val);
		else
		{
			ft_error("Syntax error", 2);
			return (1);
		}
	}
	else if (token->token == APPEND_IN)
	{
		if (!check_heredoc(token, cmd))
			ft_heredoc(token->next->val);
		else
		{
			ft_error("Syntax error", 2);
			return (1);
		}
	}
	return (0);
}

int	find_pipe(t_token *token, t_cmd *cmd)
{
	if (!check_pipe_position(token, cmd))
		cmd->pipe = true;
	else
	{
		ft_error("syntax error near unexpected token `|'", 2);
		return (1);
	}
	return (0);
}

void	find_token(t_token *token, t_cmd *cmd)
{
	if (token->token == PIPE)
		find_pipe(token, cmd);
	if (token->token == REDIR_OUT || token->token == REDIR_IN)
		find_redir(token, cmd);
	if (token->token == APPEND_OUT || token->token == APPEND_IN)
		find_append(token, cmd);
}
