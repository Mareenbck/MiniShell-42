/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:13:37 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/09 17:21:31 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lex_bis(char *str, t_token *token, int i)
{
	int	quotes;

	quotes = 0;
	while (str[i] && ft_isprint(str[i]))
	{
		if (is_doble_quotes(str[i]) || is_simple_quotes(str[i]))
		{
			if (quotes == 1)
				quotes = 0;
			else
				quotes = 1;
		}
		if ((quotes == 0 && ft_isspace(str[i]))
			|| (quotes == 0 && ft_operator(str[i])))
			break ;
		i++;
	}
	token->len = i;
	if (str[0] == '$')
		token->expand = 1;
	token->val = ft_strdup_bis(&str[i - token->len], token->len);
}

int	ft_lex(char *str, t_token *token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) && !ft_isspace(str[i]) && !ft_operator(str[i]))
		{
			ft_lex_bis(str, token, i);
			return (WORD);
		}
		else if (ft_strchr("><|\n", str[i]))
		{
			token->token = ft_find_operator(str[i], str[i + 1]);
			if (token->token == APPEND_IN || token->token == APPEND_OUT)
				token->len = 2;
			else
				token->len = 1;
			token->val = ft_strdup_bis(&str[i], token->len);
			return (token->token);
		}
		i++;
	}
	return (0);
}
