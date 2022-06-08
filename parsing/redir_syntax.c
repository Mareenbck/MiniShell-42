/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:55:28 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/08 20:35:34 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_append_o(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		return (1);
	return (0);
}

int	check_heredoc(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
		return (1);
	return (0);
}

int	check_redir_i_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if ((token->next->token != WORD && token->next != NULL)
		|| token->prev == NULL || token->next->token != WORD)
	{
		perror("Error syntax");
		return (1);
	}
	return (0);
}

int	check_redir_o_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
	{
		perror("Error Syntax");
		return (1);
	}
	return (0);
}

int	check_ambiguious_args(char *file_name, t_cmd *cmd)
{
	(void)cmd;
	if (file_name[0] == '$')
		return (1);
	return (0);
}
