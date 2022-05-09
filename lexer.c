/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:19:12 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/04 14:51:02 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_init_token()
{
  t_token *new_token;

  new_token = malloc(sizeof(t_token));
  if (!new_token)
    return (NULL);
  new_token->val = NULL;
  new_token->len = 0;
  new_token->token = 0;
  new_token->expand = 0;
  new_token->next = NULL;
  new_token->prev = NULL;
  return (new_token);
}

t_token  *create_token(char *str)
{
  t_token *new_token;

  new_token = ft_init_token();
  new_token->token = ft_lex(str, new_token);
  new_token->next = NULL;
  new_token->prev = NULL;
  return (new_token);
}

void ft_print(t_token **head)
{
	t_token *tmp;

	tmp = *head;
	int i = 0;

	while (tmp != NULL)
	{
		printf("%d > token : %d, size : %d, data : %s \n", i, tmp->token, tmp->len, tmp->val);
		i++;
		tmp = tmp->next;
	}
}

void init_line(char *line, t_token **head)
{
	int	i;
	t_token	*new;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
		{
			ft_strtrim(line, &line[i]);
			i++;
		}
		if (line[i] == '\0')
			break ;
		new = create_token(&line[i]);
		if (new->expand)
			i++;
		ft_lstaddback(head, new);
		i += new->len;
	}
	ft_lstaddback(head, ft_init_token());
	ft_print(head);
	// return (0);
}

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
	else if (c == '\n')
		return (NEW_LINE);
	else if (c == '|')
		return (PIPE);
	else
		return (0);
}

int    ft_operator(char c)
{
    if (c != '|' && c != '>' && c != '<')
        return (1);
    else
        return (0);
}

int	ft_lex(char *str, t_token *token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) && !ft_isspace(str[i]) && ft_operator(str[i]))
		{
			while (str[i] && ft_isprint(str[i]) && !ft_isspace(str[i]))
				i++;
			token->len = i;
			if (str[0] == '$')
			{
				token->len -= 1;
				token->expand = 1;
			}
			token->val = ft_strdup_bis(&str[i - token->len], token->len);
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
