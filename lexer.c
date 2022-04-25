/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:19:12 by emcariot          #+#    #+#             */
/*   Updated: 2022/04/20 13:19:35 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int	ft_find_operator(char c, char c1)
{
  if (c == '>')
  {
    if (c1 == '>')
      return (APPEND_OUT);
		return (REDIR_OUT);
  }
	else if (c == '<')
  {
    if (c1 == '<')
      return (APPEND_IN);
		return (REDIR_IN);
  }
  else if (c == '.')
  {
    if (c1 == '.')
      return (DOUBLE_POINT);
    return (POINT);
  }
  else if (c == '\'')
    return (SIMPLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	else if (c == '$')
		return (DOLLAR);
	else if (c == '=')
		return (ASSIGN);
  else if (c == '-')
    return (MINUS);
  else if (c == '|')
    return (PIPE);
  else if (c == ' ')
    return (SPACE);
  else
		return (0);
}

int	ft_lex(char *str, t_token *token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
		{
			while (str[i] && ft_isalnum(str[i]))
        i++;
      token->len = i;
      token->val = ft_strdup_bis(&str[i - token->len], token->len);
			return (WORD);
		}
    //AJOUTER CONDITION SI "" >> WORD OU DANS PARSING
		else if (ft_strchr("><\'\"$=-|.", str[i]))
    {
      token->token = ft_find_operator(str[i], str[i + 1]);
      if (token->token == APPEND_IN || token->token == APPEND_OUT || token->token == DOUBLE_POINT)
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
