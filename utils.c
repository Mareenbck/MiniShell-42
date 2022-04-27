/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:08:26 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/27 10:03:35 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	**ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	ft_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

t_token	*lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void ft_lstaddback(t_token **alst, t_token *new)
{
  if (alst)
  {
    if (*alst != NULL)
      lstlast(*alst)->next = new;
    else
      (*alst) = new;
  }
}

void ft_lst_delone(t_token *token, void (*del)(void *))
{
	if (!del || !token)
		return;
	if (token)
		(*del)(token);
}

void ft_lst_clear(t_token **head, void (*del)(void *))
{
	t_token *tmp;

	if (!del || !head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		ft_lst_delone(*head, del);
		(*head) = tmp;
	}

}

char *ft_strdup_bis(const char *s1, int len)
{
  char *str;

  str = (char *)malloc(sizeof(char) * (len + 1));
  if (!str)
    return (NULL);
  str[len] = '\0';
  len--;
  while (s1[len])
  {
    str[len] = s1[len];
    len--;
  }
  return (str);
}

// void	ft_add_back(t_liste *list, char *val)
// {
// 	t_elemt	*new;
// 	t_elemt	*last;

// 	new = malloc(sizeof(t_elemt));
// 	if (!new)
// 		return ;
// 	if (list == NULL)
// 		ft_error("Error\n");
// 	new->val = val;
// 	new->pipe = 0;
// 	new->next = NULL;
// 	if (list->head != NULL)
// 	{
// 		last = ft_lst_last(list->head);
// 		last->next = new;
// 	}
// 	else
// 		list->head = new;
// }
