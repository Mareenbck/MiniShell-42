/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:07:35 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/09 11:48:01 by mbascuna         ###   ########.fr       */
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

// void	ft_print_cmd(t_cmd **cmd)
// {
// 	t_cmd	*tmp;
// 	int		i;

// 	tmp = *cmd;
// 	i = 0;
// 	while (tmp != NULL)
// 	{
// 		i = 0;
// 		while (tmp->val[i])
// 		{
// 			printf("cmd[%d] = %s , -> expand : %d, -> pipe : %d -> output : %d -> input : %d\n", i, tmp->val[i], tmp->expand[i], tmp->pipe, tmp->output, tmp->input);
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }

int	analize_cmd(t_cmd **comd, t_global *global)
{
	t_token	*token;
	t_cmd	*cmd;

	token = global->head;
	cmd = create_cmd(list_len(&global->head));
	while (token->next != NULL)
	{
		token = ft_fill_cmdval(cmd, token);
		if (token->token == PIPE)
		{
			cmd = ft_fill_pipe(token, cmd, global);
			if (!cmd)
				return (1);
			else
				token = token->next;
		}
		token = ft_if_redir(cmd, token);
		if (!token)
			return (1);
		token = ft_if_append(cmd, token);
		if (!token)
			return (1);
	}
	ft_lstaddback2(comd, cmd);
	ft_lstaddback2(comd, ft_init_cmd(list_len(&global->head)));
	return (0);
}
