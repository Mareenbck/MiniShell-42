/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:55:28 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/17 15:26:46 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_append_o(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
	{
		printf("Syntax Error\n");
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

int	check_heredoc(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
	{
		printf("Syntax Error\n");
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

int	check_redir_i_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if ((token->next->token != WORD && token->next != NULL)
		|| token->next->token != WORD)
	{
		printf("Error syntax\n");
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

int	check_redir_o_position(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (token->next->token != WORD && token->next != NULL)
	{
		printf("Syntax Error\n");
		g_exit_status = 2;
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
