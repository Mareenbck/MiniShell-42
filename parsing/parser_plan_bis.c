/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:14:08 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/08 19:36:19 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	find_redir(t_token *token, t_cmd *cmd)
// {
// 	if (token->token == REDIR_OUT)
// 	{
// 		if (check_redir_o_position(token, cmd) == 1)
// 		{
// 			return (1);
// 		}
// 		token = token->next;
// 		if (check_ambiguious_args(token->val, cmd))
// 		{
// 			ft_error("ambiguous redirect", 2);
// 			ft_lst_clear2(&cmd, free);
// 			return (1);
// 		}
// 		else
// 			redir_out(cmd, token->val);
// 	}
// 	else if (token->token == REDIR_IN)
// 	{
// 		if (check_redir_i_position(token, cmd) == 1)
// 			return (1);
// 		token = token->next;
// 		if (check_access(cmd, token->val))
// 		{
// 			perror(token->val);
// 			ft_lst_clear2(&cmd, free);
// 			return (1);
// 		}
// 	}
// 	else if (token->token == APPEND_OUT)
// 	{
// 		if (!check_append_o(token, cmd))
// 		{
// 			token = token->next;
// 			append_out(cmd, token->val);
// 		}
// 		else
// 		{
// 			ft_error("Syntax error", 2);
// 			ft_lst_clear2(&cmd, free);
// 			return (1);
// 		}
// 	}
// 	else if (token->token == APPEND_IN)
// 	{
// 		if (!check_heredoc(token, cmd))
// 		{
// 			token = token->next;
// 			ft_heredoc(token->val);
// 		}
// 		else
// 		{
// 			ft_error("Syntax error", 2);
// 			ft_lst_clear2(&cmd, free);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }
