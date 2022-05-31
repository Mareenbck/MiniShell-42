/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:02:21 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/31 15:02:24 by emcariot         ###   ########.fr       */
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

void	trim_doble_quotes(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->val[i])
	{
		j = 0;
		while (cmd->val[i][j])
		{
			if (is_doble_quotes(cmd->val[i][j]))
				cmd->val[i] = ft_strtrim(cmd->val[i], "\'");
			j++;
		}
		i++;
	}
}

void	trim_simple_quotes(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->val[i])
	{
		j = 0;
		while (cmd->val[i][j])
		{
			if (is_simple_quotes(cmd->val[i][j]))
				cmd->val[i] = ft_strtrim(cmd->val[i], "\'");
			j++;
		}
		i++;
	}
}
