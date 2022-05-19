/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:48:27 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/18 09:56:35 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd *ft_init_cmd(int len)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->val = (char **)malloc(sizeof(t_token) * len + 1);
	new_cmd->expand = (int *)malloc(sizeof(t_token) * len);
	new_cmd->index = (int *)malloc(sizeof(t_token) * len);
	new_cmd->path = NULL;
	new_cmd->next = NULL;
	new_cmd->pipe = false;
	return (new_cmd);
}

t_cmd *create_cmd(int len)
{
	t_cmd *new_cmd;

	new_cmd = ft_init_cmd(len);
	*new_cmd->val = NULL;
	*new_cmd->expand = 0;
	*new_cmd->index = 0;
	new_cmd->path = NULL;
	new_cmd->next = NULL;
	new_cmd->output = 0;
	new_cmd->input = 0;
	new_cmd->pipe = false;
	new_cmd->count = 0;
	return (new_cmd);
}

void	ft_print_cmd(t_cmd **cmd)
{
	t_cmd *tmp;
	int i = 0;

	tmp = *cmd;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->val[i])
		{
			printf("cmd[%d] = %s , -> expand : %d, -> pipe : %d\n", i, tmp->val[i], tmp->expand[i], tmp->pipe);
			i++;
		}
		tmp = tmp->next;
	}
}

void	analize_redir(t_token *token, t_cmd *cmd)
{
	int	type;

	type = 0;
	if (token->token == REDIR_OUT)
	{
		check_redir_o_position(token, cmd);
		create_file(token, type);
	}
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

void	initialize_io(t_cmd *cmd)
{
		cmd->input = STDIN_FILENO;
		cmd->output = STDOUT_FILENO;
}

int	list_len(t_token **head)
{
	t_token *token;
	token = *head;
	int len = 0;

	while (token)
	{
		len++;
		token = token->next;
	}
	return (len);
}

int	analize_cmd(t_token **head, t_cmd **comd)
{
	t_token *token;
	t_cmd	*cmd;
	token = *head;
	int	i;
	int len;

	len = list_len(head);
	while (token != NULL)
	{
		i = 0;
		cmd = create_cmd(len);
		cmd->index[i] = i;
		while (token->token == WORD)
		{
			cmd->expand[i] = 0;
			if (token->expand)
			{
                cmd->val[i] = ft_strdup(&token->val[1]);
				cmd->expand[i] = 1;
			}
			else
				cmd->val[i] = ft_strdup(token->val);
			token = token->next;
			i++;
		}
		cmd->val[i] = NULL;
		cmd->count = i;
		if (token->token == PIPE || token->prev->token == PIPE)
		{
			if (!check_pipe_position(token, cmd))
			{
				cmd->pipe = true;
			}
			else
			{
				ft_error("syntax error near unexpected token `|'", 2);
				return (1);
			}
		}
		else if (token->token == REDIR_OUT || token->token == REDIR_IN)
			analize_redir(token, cmd);
		else if (token->token == APPEND_OUT || token->token == APPEND_IN)
			analize_append(token, cmd);
		initialize_io(cmd);
		cmd->index++;
		ft_lstaddback2(comd, cmd);
		token = token->next;
	}
	ft_lstaddback2(comd, ft_init_cmd(len));
	// ft_print_cmd(comd);
	return (0);
}
