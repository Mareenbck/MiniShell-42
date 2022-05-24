/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:41:37 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/17 11:52:46 by emcariot         ###   ########.fr       */
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

int	start_with_simple(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->val[i])
	{
		j = 0;
		if (cmd->val[i][j] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	start_with_dobles(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->val[i])
	{
		j = 0;
		if (cmd->val[i][j] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int start_with_dollar(t_cmd *cmd)
{
	int i;
	int j;

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

int is_empty_string(char *str)
{
	if (is_doble_quotes(str[0]) && is_doble_quotes(str[1]) && ft_isspace(str[2]))
		return (1);
	else if (is_simple_quotes(str[0]) && is_simple_quotes(str[1]) && ft_isspace(str[2]))
		return (1);
	else
		return (0);
}
