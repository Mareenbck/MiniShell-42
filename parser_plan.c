/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:48:27 by emcariot          #+#    #+#             */
/*   Updated: 2022/04/26 13:15:40 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void recup_token(t_token *new_tok, t_global *global)
{
	t_token *tmp;
	char *cmd;
	int i;

	i = 0;
	tmp = new_tok;
	while (tmp != NULL)
	{
		if (tmp->token == 9)
		{
			if (execve(tmp->val, tmp->next, global->env) == -1)
			{
				printf("%s", tmp->val);
			}
		}
		tmp = tmp->next;
	}
}