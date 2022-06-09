/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:17 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/09 14:57:17 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_go_expand_echo(t_cmd *cmd, t_global *global, char *tmp)
{
	ft_expand_echo(cmd, global, cmd->val[0]);
	free(tmp);
	ft_free_list(global);
	return (1);
}
