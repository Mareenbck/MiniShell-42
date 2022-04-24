/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marinebascunana <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:39:45 by marinebas         #+#    #+#             */
/*   Updated: 2022/04/21 11:39:47 by marinebas        ###   ########.fr       */
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
  return (new_token);
}

t_token  *create_token(char *str)
{
  t_token *new_token;

  new_token = ft_init_token();
  new_token->token = ft_lex(str, new_token);
  new_token->next = NULL;
  return (new_token);
}

void ft_print(t_token *head)
{
  t_token *tmp;
  int i = 0;

  tmp = head;
  while (tmp != NULL)
  {
    printf("%d > token : %d, size : %d, data : %s\n", i, tmp->token, tmp->len, tmp->val);
    i++;
    tmp = tmp->next;
  }
}

void init_line(char *line, t_token **head)
{
  int i;
  t_token *new;

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
  ft_print(*head);
}

// tant que espaces au debut on avance
//si espace on rentre token data et aadd back list

//creer un nouveau token a chaque fois
// que tu add back a la liste
// tkoen a le token, la data

//pour passer au suivant, il faut mesurer la taille du mot
