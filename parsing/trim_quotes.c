/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 08:34:27 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/06 13:19:31 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_doble_quotes(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

int		is_simple_quotes(char c)
{
	if (c == 39)
		return (1);
	return (0);
}


void		trim_doble_quotes(t_token *token)
{
	int	i;

	while (token->token == WORD)
	{
		i = 0;
		while (token->val[i])
		{
			if (is_doble_quotes(token->val[i]))
			{
				printf("i = %d\n", i);
				token->val = ft_strtrim(token->val, "\"");
				printf("token->val[i] = %c\n", token->val[i]);
			}
			i++;
		}
		token = token->next;
	}
}

void		trim_simple_quotes(t_token *token)
{
	int	i;

	while (token->token == WORD)
	{
		i = 0;
		while (token->val[i])
		{
			if (is_simple_quotes(token->val[i]))
			{
				printf("i = %d\n", i);
				token->val = ft_strtrim(token->val, "\'");
				printf("token->val[i] = %c\n", token->val[i]);
			}
			i++;
		}
		token = token->next;
	}
}
