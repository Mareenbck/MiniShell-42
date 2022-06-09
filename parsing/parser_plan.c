/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:07:35 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/09 09:55:49 by mbascuna         ###   ########.fr       */
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
	while (token)
	{
		len++;
		token = token->next;
	}
	return (len);
}

void	ft_print_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = *cmd;
	i = 0;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->val[i])
		{
			printf("cmd[%d] = %s , -> expand : %d, -> pipe : %d -> output : %d -> input : %d\n", i, tmp->val[i], tmp->expand[i], tmp->pipe, tmp->output, tmp->input);
			i++;
		}
		tmp = tmp->next;
	}
}

int	analize_cmd(t_cmd **comd, t_global *global)
{
	t_token	*token;
	t_cmd	*cmd;
	// int		i;
	token = global->head;
	cmd = create_cmd(list_len(&global->head));
	// i = 0;
	while (token != NULL)
	{
		token = ft_fill_cmdval(cmd, token);
		if (token->token == PIPE)
		{
			cmd = ft_fill_pipe(token, cmd, global);
			if (!cmd)
				return (1);
		}
		else if (token->token == REDIR_OUT)
		{
			if (check_redir_out(token, cmd) == 0)
				token = token->next;
		}
		else if (token->token == REDIR_IN)
		{
			if (check_redir_in(token, cmd) == 0)
				token = token->next;
		}
		else if (token->token == APPEND_OUT)
		{
			if (ana_append_out(token, cmd) == 0)
				token = token->next;
		}
		else if (token->token == APPEND_IN)
		{
			if (ana_append_in(token, cmd) == 0)
				token = token->next;
		}
		token = token->next;
	}
	ft_lstaddback2(comd, cmd);
	ft_lstaddback2(comd, ft_init_cmd(list_len(&global->head)));
	return (0);
}

// int	analize_cmd(t_cmd **comd, t_global *global)
// {
// 	t_token	*token;
// 	t_cmd	*cmd;
// 	int		i;

// 	token = global->head;
// 	cmd = create_cmd(list_len(&global->head));
// 	i = 0;
// 	while (token != NULL)
// 	{
// 		while (token->token == WORD)
// 		{
// 			cmd->expand[i] = 0;
// 			if (token->expand)
// 				cmd->expand[i] = 1;
// 			cmd->val[i] = ft_strdup(token->val);
// 			token = token->next;
// 			i++;
// 		}
// 		cmd->val[i] = NULL;
// 		if (token->token == PIPE)
// 		{
// 			if (!check_pipe_position(token, cmd))
// 			{
// 				cmd->pipe = true;
// 				ft_lstaddback2(comd, cmd);
// 				cmd = create_cmd(list_len(&global->head));
// 				i = 0;
// 			}
// 			else
// 			{
// 				ft_error("syntax error near unexpected token `|'", 2);
// 				ft_lst_clear2(&cmd, free);
// 				return (1);
// 			}
// 		}
// 		else if (token->token == REDIR_OUT)
// 		{
// 			if (check_redir_o_position(token, cmd) == 1)
// 			{
// 				return (1);
// 			}
// 			token = token->next;
// 			if (check_ambiguious_args(token->val, cmd))
// 			{
// 				ft_error("ambiguous redirect", 2);
// 				ft_lst_clear2(&cmd, free);
// 				return (1);
// 			}
// 			else
// 				redir_out(cmd, token->val);
// 		}
// 		else if (token->token == REDIR_IN)
// 		{
// 			if (check_redir_i_position(token, cmd) == 1)
// 				return (1);
// 			token = token->next;
// 			if (check_access(cmd, token->val))
// 			{
// 				perror(token->val);
// 				ft_lst_clear2(&cmd, free);
// 				return (1);
// 			}
// 		}
// 		else if (token->token == APPEND_OUT)
// 		{
// 			if (!check_append_o(token, cmd))
// 			{
// 				token = token->next;
// 				append_out(cmd, token->val);
// 			}
// 			else
// 			{
// 				ft_error("Syntax error", 2);
// 				ft_lst_clear2(&cmd, free);
// 				return (1);
// 			}
// 		}
// 		else if (token->token == APPEND_IN)
// 		{
// 			if (!check_heredoc(token, cmd))
// 			{
// 				token = token->next;
// 				ft_heredoc(token->val);
// 			}
// 			else
// 			{
// 				ft_error("Syntax error", 2);
// 				ft_lst_clear2(&cmd, free);
// 				return (1);
// 			}
// 		}
// 		token = token->next;
// 	}
// 	ft_lstaddback2(comd, cmd);
// 	ft_lstaddback2(comd, ft_init_cmd(list_len(&global->head)));
// 	return (0);
// }
