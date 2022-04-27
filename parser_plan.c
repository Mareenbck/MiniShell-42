/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:48:27 by emcariot          #+#    #+#             */
/*   Updated: 2022/04/27 17:37:52 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *ft_init_cmd()
{
  t_cmd *new_cmd;

  new_cmd = malloc(sizeof(t_cmd));
  if (!new_cmd)
    return (NULL);
  new_cmd->value = NULL;
  new_cmd->option = NULL;
  new_cmd->next = NULL;
  return (new_cmd);
}

int	count_option(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '-')
			count++;
		i++;
	}
	return (count);
}

void	analize_cmd(t_token **head, t_cmd **comd)
{
	t_token *token;
	t_cmd	*cmd;
	token = *head;
	
	cmd = ft_init_cmd();
	while (token != NULL)
	{
		while (token->next != NULL && token->token != PIPE)
		{
			if (token->token == WORD && (token->prev == NULL || token->prev->token == PIPE))
				cmd->value = ft_strdup_bis(token->val, token->len);
			// COMMENT REMPLIR LES ARGS
			if (token->token == WORD && cmd->value != NULL)
				cmd->arg = ft_strdup_bis(token->val, token->len);
			if (token->token == MINUS)
				cmd->option = ft_strdup_bis(token->next->val, token->next->len);
			token = token->next;
			printf("cmd value : %s, option : %s, next : %p , arg : %s\n", cmd->value, cmd->option, cmd->next, cmd->arg);
		}
		ft_lstaddback2(comd, cmd);
		if (token->token == PIPE)
			cmd = ft_init_cmd();
		token = token->next;
	}
	ft_lstaddback2(comd, ft_init_cmd());
	ft_print_cmd(comd);
}
// void	analise_pipe(t_token **head, t_cmd **comd)
// {
// 	t_token *token;
// 	t_cmd	*cmd;

// 	while (token->token != PIPE)
// }

void	ft_print_cmd(t_cmd **cmd)
{
	t_cmd *tmp;

	tmp = *cmd;
	while (tmp != NULL)
	{
		printf("value = %s, option = %s, next : %p, arg : %s\n", tmp->value, tmp->option, tmp->next, tmp->arg);
		tmp = tmp->next;
	}
}