/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:48:27 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/06 09:00:33 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd *ft_init_cmd()
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->val = (char **)malloc(sizeof(char *));
	new_cmd->next = NULL;
	return (new_cmd);
}


void	ft_print_cmd(t_cmd **cmd)
{
	t_cmd *tmp;
	int i = 0;

	tmp = *cmd;
	while (tmp->next != NULL)
	{
		i = 0;
		while (tmp->val[i] != NULL)
		{
			printf("mot[%d] = %s\n", i, tmp->val[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

void	analize_redir(t_token *token, t_cmd *cmd)
{
	if (token->token == REDIR_OUT)
		check_redir_o_position(token, cmd);
	if (token->token == REDIR_IN)
		check_redir_i_position(token, cmd);
}

void	analize_append(t_token *token, t_cmd *cmd)
{
	if (token->token == APPEND_OUT)
		check_append_o(token, cmd);
	if (token->token == APPEND_IN)
		check_append_i(token, cmd);
}

void	analize_cmd(t_token **head, t_cmd **comd)
{
	t_token *token;
	t_cmd	*cmd;
	token = *head;
	int	i;

	cmd = ft_init_cmd();
	while (token != NULL)
	{
		i = 0;
		while (token->token == WORD && token->token != PIPE)
		{
			if (token->expand)
			{
				cmd->val[i] = ft_strdup(&token->val[1]);
				cmd->expand = 1;
			}
			else
				cmd->val[i] = ft_strdup(token->val);
			i++;
			token = token->next;
		}
		cmd->val[i] = NULL;
		ft_lstaddback2(comd, cmd);
		if (token->token == REDIR_OUT || token->token == REDIR_IN)
			analize_redir(token, cmd);
		if (token->token == PIPE)
		{
			cmd = ft_init_cmd();
			check_pipe_position(token, cmd);
		}
		if (token->token == APPEND_OUT || token->token == APPEND_IN)
			analize_append(token, cmd);
		token = token->next;
	}
	ft_lstaddback2(comd, ft_init_cmd());
	ft_print_cmd(comd);
}
