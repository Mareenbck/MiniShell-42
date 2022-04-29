/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:48:27 by emcariot          #+#    #+#             */
/*   Updated: 2022/04/29 10:46:45 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *ft_init_cmd()
{
  t_cmd *new_cmd;

  new_cmd = malloc(sizeof(t_cmd));
  if (!new_cmd)
    return (NULL);
	new_cmd->val = (char **)malloc(sizeof(char *));
//   new_cmd->val = NULL;
  new_cmd->next = NULL;
  return (new_cmd);
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
		while (token != NULL && token->token != PIPE)
		{
			printf("i =  %d\n", i);
			if (token->token == WORD)
			{
				//if (token->prev == NULL || token->prev->token == PIPE)
				cmd->val[i] = ft_strdup(token->val);
				printf("cmd->val[%d] = %s\n", i, cmd->val[i]);
			}
			i++;
			token = token->next;
		}
		cmd->val[i] = NULL;
		ft_lstaddback2(comd, cmd);
		if (token->token == PIPE || token->token == 0)
			cmd = ft_init_cmd();
		// printf("token->next %s\n", token->next->val);
		token = token->next;
	}
	ft_lstaddback2(comd, ft_init_cmd());
	ft_print_cmd(comd);
}

//
void	ft_print_cmd(t_cmd **cmd)
{
	t_cmd *tmp;
	int i = 0;

	tmp = *cmd;
	while (tmp->val[i] != NULL)
	{
		printf("mot[%d] = %s\n", i, tmp->val[i]);
		i++;
		// tmp = tmp->va;
	}
}
