/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:26:05 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/06 14:25:44 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_s_quotes_positon(t_token *token)
{
	int	i;

	i = 0;
	while (token->val[i])
	{
		if (is_simple_quotes(token->val[i]))
		{

		}

	}
}
