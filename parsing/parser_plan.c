/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:18:45 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/20 14:06:03 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_init_cmd(int len)
{
	t_cmd	*new_cmd;
	int		i;

	i = 0;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->val = (char **)malloc(sizeof(t_token) * len + 1);
	while (i <= len)
		new_cmd->val[i++] = NULL;
	new_cmd->expand = (int *)malloc(sizeof(t_token) * len);
	new_cmd->path = NULL;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	new_cmd->pipe = false;
	new_cmd->pid = -1;
	return (new_cmd);
}

t_cmd	*create_cmd(int len)
{
	t_cmd	*new_cmd;

	new_cmd = ft_init_cmd(len);
	*new_cmd->val = NULL;
	*new_cmd->expand = 0;
	new_cmd->path = NULL;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	new_cmd->output = STDOUT_FILENO;
	new_cmd->input = STDIN_FILENO;
	new_cmd->pipe = false;
	new_cmd->count = 0;
	new_cmd->pid = -1;
	return (new_cmd);
}

int	list_len(t_token **head)
{
	t_token	*token;
	int		len;

	token = *head;
	len = 0;
	while (token->next)
	{
		len++;
		token = token->next;
	}
	return (len);
}

t_cmd	*ft_init_heredoc(t_global *global, t_cmd *cmd)
{
	if ((global->head->token == APPEND_IN
			|| global->head->next->token == APPEND_IN) && cmd->val[0]
		&& !ft_strncmp(cmd->val[0], "cat", 3))
	{
		cmd->val[1] = ft_strdup(".here_doc");
		cmd->expand[1] = 0;
	}
	return (cmd);
}

int	analize_cmd(t_cmd **comd, t_global *global)
{
	t_token	*token;
	t_cmd	*cmd;

	token = global->head;
	cmd = create_cmd(list_len(&global->head));
	while (token->next != NULL)
	{
		if (token->token == WORD)
			token = ft_fill_cmdval(cmd, token);
		if (token->token == PIPE)
		{
			cmd = ft_fill_pipe(token, cmd, global);
			if (!cmd)
				return (1);
			token = token->next;
		}
		token = ft_if_operator(cmd, token, global);
		if (!token)
			return (1);
		ft_init_heredoc(global, cmd);
	}
	ft_lstaddback2(comd, cmd);
	ft_lstaddback2(comd, ft_init_cmd(list_len(&global->head)));
	return (0);
}
