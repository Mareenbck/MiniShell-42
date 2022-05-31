/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:41:37 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/31 14:58:13 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_d_quotes(t_cmd *cmd)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (cmd->val[i])
	{
		j = 0;
		while (cmd->val[i][j])
		{
			if (is_doble_quotes(cmd->val[i][j]))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	count_s_quotes(t_cmd *cmd)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (cmd->val[i])
	{
		j = 0;
		while (cmd->val[i][j])
		{
			if (is_simple_quotes(cmd->val[i][j]))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	start_with_simple(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->val[i])
	{
		if (cmd->val[i][0] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	start_with_dobles(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->val[i])
	{
		if (cmd->val[i][0] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	start_with_dollar(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->val[i])
	{
		j = 0;
		if (cmd->val[i][j] == '$')
			return (1);
		i++;
	}
	return (0);
}
