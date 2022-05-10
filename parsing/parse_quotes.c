/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:26:05 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/10 11:40:27 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_d_quotes(t_token *token)
{
	int	i;
	int count;

	count = 0;
	while (token->token == WORD)
	{
		i = 0;
		while (token->val[i])
		{
			if (is_doble_quotes(token->val[i]))
				count++;
			i++;
		}
		token = token->next;
	}
	return (count);
}

int	count_s_quotes(t_token *token)
{
	int	i;
	int count;

	count = 0;
	while (token->token == WORD)
	{
		i = 0;
		while (token->val[i])
		{
			if (is_simple_quotes(token->val[i]))
				count++;
			i++;
		}
		token = token->next;
	}
	return (count);
}

void	recup_count_d_quotes(t_token *token)
{
	int countd;

	countd = count_d_quotes(token);
	if (countd % 2 == 0)
		trim_doble_quotes(token);
	else
		ft_error("Command not found\n");
}

void	recup_count_s_quotes(t_token *token)
{
	int counts;

	counts = count_s_quotes(token);
	if (counts % 2 == 0)
		trim_simple_quotes(token);
	else
		ft_error("Command not found");
}
