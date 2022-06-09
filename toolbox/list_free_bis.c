/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:54:00 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/09 13:34:26 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_only_list(t_global *global)
{
	ft_lst_clear3(&global->head_env, free);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	perror("");
	// perror("Command Not Found2");
}

int	ft_free_list_and_error(t_global *global)
{
	ft_lst_clear3(&global->head_env, free);
	ft_lst_clear(&global->head, free);
	ft_lst_clear2(&global->headcmd, free);
	ft_free_tab(global->env);
	perror("Command Not Found1");
	return (1);
}
