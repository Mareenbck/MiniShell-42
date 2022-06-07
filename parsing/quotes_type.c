/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:02:21 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/07 16:38:05 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_doble_quotes(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

int	is_simple_quotes(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

int	start_with_simple(char *cmd)
{
	if (cmd[0] == '\'')
		return (1);
	else
		return (0);
}

int	start_with_dobles(char *cmd)
{
	if (cmd[0] == '\"')
		return (1);
	else
		return (0);
}

int	start_with_dollar(char *cmd)
{
	if (cmd[0] == '$')
		return (1);
	else
		return (0);
}
