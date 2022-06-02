/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:34:42 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/01 16:39:47 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool find_n(char *str, char c)
{
	int i;
	i = 0;
	while (str[i] == c)
		i++;
	if (str[i] == '\0')
		return (true);
	else
		return (false);
}

int ft_echo(t_cmd *cmd, t_global *global)
{
	int option;
	int i;

	option = 0;
	i = 1;
	while (cmd->val[i] != NULL && !ft_strncmp(cmd->val[i], "-n", 2) && find_n(&cmd->val[i][1], 'n'))
	{
		option = 1;
		i++;
	}
	while (cmd->val[i] != NULL)
	{
		if (cmd->expand[i])
			ft_expand_echo(cmd, global, cmd->val[i]);
		else
		{
			if (start_with_dollar(cmd) && cmd->expand[i])
				write(cmd->output, &cmd->val[i][1], ft_strlen(&cmd->val[i][1]));
			else if (start_with_dollar(cmd) && !cmd->expand[i])
				write(cmd->output, cmd->val[i], ft_strlen(cmd->val[i]));
			else
				write(cmd->output, cmd->val[i], ft_strlen(cmd->val[i]));
		}
		i++;
	}
	if (!option)
	{
		printf("\n");
	}
	return (0);
}
