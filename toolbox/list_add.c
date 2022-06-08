/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:35:30 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/08 11:39:09 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstaddback(t_token **alst, t_token *new)
{
	t_token	*tmp;

	if (alst)
	{
		if (*alst != NULL)
		{
			tmp = *alst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
			new->next = NULL;
		}
		else
			(*alst) = new;
	}
}

void	ft_lstaddback2(t_cmd **alst, t_cmd *new)
{
	t_cmd	*tmp;

	if (alst)
	{
		if (*alst != NULL)
		{
			tmp = *alst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
			new->next = NULL;
		}
		else
			(*alst) = new;
	}
}

void	ft_lstaddback3(t_env **alst, t_env *new)
{
	t_env	*tmp;

	if (alst)
	{
		if (*alst != NULL)
		{
			tmp = *alst;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
			new->next = NULL;
		}
		else
			(*alst) = new;
	}
}

void	ft_lstaddfront(t_env **alst, t_env *new)
{
	t_env	*tmp;

	tmp = *alst;
	new->next = *alst;
	tmp->prev = new;
	*alst = new;
}
