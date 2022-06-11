/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:41:33 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/08 11:42:00 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_clear(t_token **head, void (*del)(void *))
{
	t_token	*tmp;

	if (!del || !head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		ft_lst_delone(*head, del);
		(*head) = tmp;
	}
}

void	ft_lst_clear2(t_cmd **head, void (*del)(void *))
{
	t_cmd	*tmp;

	if (!del || !head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		ft_free_tab((*head)->val);
		ft_lst_delone2(*head, del);
		(*head) = tmp;
	}
}

void	ft_lst_clear3(t_env **head, void (*del)(void *))
{
	t_env	*tmp;

	if (!del || !head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		ft_lst_delone3(*head, del);
		(*head) = tmp;
	}
}
