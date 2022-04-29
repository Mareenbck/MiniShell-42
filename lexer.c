/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:19:12 by emcariot          #+#    #+#             */
/*   Updated: 2022/04/29 10:47:19 by emcariot         ###   ########.fr       */
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
	// if (tmp->prev != NULL)
	//     printf("%d > token : %d, size : %d, data : %s \n", i, tmp->token, tmp->len, tmp->val);
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
		if (ft_isspace(line[i]))
		{
			ft_strtrim(line, &line[i]);
			i++;
		}
		if (line[i] == '\0')
			break;
		new = create_token(&line[i]);
		ft_lstaddback(head, new);
		i += new->len;
	}
	ft_lstaddback(head, ft_init_token());
	ft_print(head);
}

// tant que espaces au debut on avance
//si espace on rentre token data et aadd back list

//creer un nouveau token a chaque fois
// que tu add back a la liste
// tkoen a le token, la data

//pour passer au suivant, il faut mesurer la taille du mot


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
  else if (c == '-' || c == '~')
   return (WORD);
  else if (c == '|')
    return (PIPE);
  else
		return (0);

}

int	ft_lex(char *str, t_token *token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '-' || str[i] == '~')
		{
			token->len = 1;
			token->val = ft_strdup_bis(&str[i], token->len);
			return (WORD);
		}
		if (ft_isalnum(str[i]))
		{
			while (str[i] && ft_isalnum(str[i]))
				i++;
			token->len = i;
			token->val = ft_strdup_bis(&str[i - token->len], token->len);
			return (WORD);
		}
    //AJOUTER CONDITION SI "" >> WORD OU DANS PARSING
		else if (ft_strchr("><|", str[i]))
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
