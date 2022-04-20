/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:12:35 by emcariot          #+#    #+#             */
/*   Updated: 2022/04/20 17:31:21 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_back(t_line *head, char *tab)
{
	t_line	*last;

	head = malloc(sizeof(t_line));
    head->val = tab;
	head->pipe = 0;
    head->next = NULL;
    if (head->next != NULL)
	{
        last = lstlast(head);
		last->next = head;
	}
	printf ("errrrr\n");
	
}

t_line *fill_linked_list(char *str)
{
	char **tab;
	int i;
	t_line *head;

	head = NULL;
	tab = ft_split(str, '|');
	i = 0;
	while (tab[i])
	{
		add_back(head, tab[i]);
		i++;
	}
	return (head);
}

void test(t_line *head)
{
	printf("hello\n");
	while (head)
	{
		printf("maillon 1 ; %s\n", head->val);
		head = head->next;
	}
}