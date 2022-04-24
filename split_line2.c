/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:55:01 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/20 14:55:02 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_lstdel(t_elemt *elemt)
// {
// 	t_elemt	*tmp;

// 	while (elemt)
// 	{
// 		tmp = elemt->next;
// 		free(elemt);
// 		elemt = tmp;
// 	}
// 	free(elemt);
// }

// t_elemt	*ft_lst_last(t_elemt *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// t_liste	*ft_list_init(void)
// {
// 	t_liste	*list;

// 	list = malloc(sizeof(t_liste));
// 	if (!list)
// 	{
// 		ft_lstdel(list->head);
// 		ft_error("Error\n");
// 	}
// 	list->head = NULL;
// 	return (list);
// }

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

// t_liste	*ft_split_pipe(char *line)
// {
// 	t_liste	*list;
// 	char **tab;
// 	int i = 0;

// 	tab = ft_split(line, '|');
// 	list = ft_list_init();
// 	while (tab[i])
// 	{
// 		ft_add_back(list, tab[i]);
// 		i++;
// 	}
// 	return (list);
// }

// void afficherListe(t_liste *list)
// {
//     if (list == NULL)
//     {
//         ft_error("Aff. List\n");
//     }

//     t_elemt	*now = list->head;

//     while (now != NULL)
//     {
//         printf("%s -> \n", now->val);
//         now = now->next;
//     }
//     printf("NULL\n");
// }
