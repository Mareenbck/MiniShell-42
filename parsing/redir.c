/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:53:14 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/04 17:40:58 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir_o_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		ft_error("error syntax 2\n");
	if (token->prev == NULL)
		ft_error("error syntax \n");
	return (0);
}

int	check_redir_i_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		ft_error("error syntax 2\n");
	if (token->prev == NULL)
		ft_error("error syntax \n");
	return (0);
}

int check_append_o(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		ft_error("syntax error2 \n");
	if (token->prev == NULL)
		ft_error("syntax error \n");
	return (0);
}

int check_append_i(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		ft_error("syntax error2 \n");
	if (token->prev == NULL)
		ft_error("syntax error \n");
	return (0);
}