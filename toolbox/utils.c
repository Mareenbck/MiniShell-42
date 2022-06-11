/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:08:26 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/08 12:14:02 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_cmd	*lstlast2(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lst_insert_bis(t_env *new, t_env *tmp)
{
	new->prev = tmp->prev;
	tmp->prev = new;
	new->next = tmp;
}

void	ft_lst_insert(t_env **head_env, t_env *new)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *head_env;
	if (head_env)
	{
		while ((ft_strcmp(new->var_name, tmp->var_name) > 0)
			&& tmp->next->var_name != NULL)
			tmp = tmp->next;
		if (tmp->next->var_name != NULL && tmp->prev != NULL)
		{
			tmp2 = tmp->prev;
			tmp2->next = new;
			ft_lst_insert_bis(new, tmp);
		}
		else if (tmp == *head_env)
			ft_lstaddfront(head_env, new);
		else
		{
			tmp2 = tmp->next;
			tmp->next = new;
			new->prev = tmp;
			new->next = tmp2;
		}
	}
}

char	*ft_strdup_bis(const char *s1, int len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (--len >= 0)
		str[len] = s1[len];
	return (str);
}
