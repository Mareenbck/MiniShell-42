/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:18:13 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/17 11:52:04 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_fill_cmdval(t_cmd *cmd, t_token *token)
{
	int	i;

	i = 0;
	if (cmd->val[i] != NULL)
		while (cmd->val[i] != NULL)
			i++;
	while (token->token == WORD)
	{
		cmd->expand[i] = 0;
		if (token->expand)
			cmd->expand[i] = 1;
		cmd->val[i] = ft_strdup(token->val);
		token = token->next;
		i++;
	}
	cmd->val[i] = NULL;
	return (token);
}

t_cmd	*ft_fill_pipe(t_token *token, t_cmd *cmd, t_global *global)
{
	if (!check_pipe_position(token, cmd))
	{
		cmd->pipe = true;
		ft_lstaddback2(&global->headcmd, cmd);
		cmd = create_cmd(list_len(&global->head));
	}
	else
	{
		ft_error("syntax error near unexpected token `|'", 2);
		g_exit_status = 2;
		ft_lst_clear2(&cmd, free);
		return (NULL);
	}
	return (cmd);
}

t_token	*ft_if_redir(t_cmd *cmd, t_token *token)
{
	if (token->token == REDIR_OUT)
	{
		token = check_redir_out(token, cmd);
		if (!token)
			return (NULL);
		else
			return (token->next);
	}
	else if (token->token == REDIR_IN)
	{
		token = check_redir_in(token, cmd);
		if (!token)
			return (NULL);
		else
			return (token->next);
	}
	return (token);
}

t_token	*ft_if_append(t_cmd *cmd, t_token *token, t_global *global)
{
	if (token->token == APPEND_OUT)
	{
		token = ana_append_out(token, cmd);
		if (!token)
			return (NULL);
		else
			return (token->next);
	}
	else if (token->token == APPEND_IN)
	{
		token = ana_append_in(token, cmd, global);
		if (!token)
			return (NULL);
		else
			return (token->next);
	}
	return (token);
}

t_token	*ft_if_operator(t_cmd *cmd, t_token *token, t_global *global)
{
	token = ft_if_redir(cmd, token);
	if (!token)
		return (NULL);
	token = ft_if_append(cmd, token, global);
	if (!token)
		return (NULL);
	return (token);
}
