/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan_ter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:31:08 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/09 18:15:55 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*check_redir_in(t_token *token, t_cmd *cmd)
{
	if (token->token == REDIR_IN)
	{
		if (check_redir_i_position(token, cmd) == 1)
		{
			ft_lst_clear2(&cmd, free);
			return (NULL);
		}
		token = token->next;
		if (check_access(cmd, token->val))
		{
			perror(token->val);
			ft_lst_clear2(&cmd, free);
			return (NULL);
		}
	}
	return (token);
}

t_token	*check_redir_out(t_token *token, t_cmd *cmd)
{
	if (token->token == REDIR_OUT)
	{
		if (check_redir_o_position(token, cmd) == 1)
		{
			ft_lst_clear2(&cmd, free);
			return (NULL);
		}
		token = token->next;
		if (check_ambiguious_args(token->val, cmd))
		{
			ft_error("ambiguous redirect", 2);
			ft_lst_clear2(&cmd, free);
			return (NULL);
		}
		else
			redir_out(cmd, token->val);
	}
	return (token);
}

t_token	*ana_append_in(t_token *token, t_cmd *cmd)
{
	if (token->token == APPEND_IN)
	{
		if (!check_heredoc(token, cmd))
		{
			token = token->next;
			ft_heredoc(token->val);
		}
		else
		{
			ft_error("Syntax error", 2);
			ft_lst_clear2(&cmd, free);
			return (NULL);
		}
	}
	return (token);
}

t_token	*ana_append_out(t_token *token, t_cmd *cmd)
{
	if (token->token == APPEND_OUT)
	{
		if (check_append_o(token, cmd) == 1)
		{
			ft_lst_clear2(&cmd, free);
			return (NULL);
		}
		token = token->next;
		if (check_ambiguious_args(token->val, cmd))
		{
			ft_error("ambiguous redirect", 2);
			ft_lst_clear2(&cmd, free);
			return (NULL);
		}
		else
			append_out(cmd, token->val);
	}
	return (token);
}
