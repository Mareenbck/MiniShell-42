/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:48:42 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/20 10:48:45 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_operator(char c)
{
	if (c == '>')
		return (REDIR_OUT);
	else if (c == '<')
		return (REDIR_IN);
	else if (c == '\'')
		return (SIMPLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	else if (c == '$')
		return (DOLLAR);
	else if (c == '=')
		return (ASSIGN);
	else
		return (0);
}

int	ft_lex(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
		{
			while (str[i] && ft_isalnum(str[i]))
				i++;
			return (WORD);
		}
		else if (ft_strchr("><\'\"$=", str[i]))
			return (ft_find_operator(str[i]));
		else
			return (0);
	}
	return (0);
}

void	ft_test_lex(char *line, t_global *global)
{
	global->token = ft_lex(line);
	printf(" Token : %d", global->token) ;
	if (global->token == WORD)
		printf(", valeur: %s\n", line);
	else
		printf ("\n");
}
