/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:28:15 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/07 19:01:44 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	find_n(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] == c)
		i++;
	if (str[i] == '\0')
		return (true);
	else
		return (false);
}

void	ft_print(t_cmd *cmd, int i)
{
	if (start_with_dollar(cmd->val[i]) && cmd->expand[i])
	{
		write(cmd->output, &cmd->val[i][1], ft_strlen(&cmd->val[i][1]));
		write(cmd->output, " ", 1);
	}
	else if (start_with_dollar(cmd->val[i]) && !cmd->expand[i])
	{
		write(cmd->output, cmd->val[i], ft_strlen(cmd->val[i]));
		write(cmd->output, " ", 1);
	}
	else
	{
		write(cmd->output, cmd->val[i], ft_strlen(cmd->val[i]));
		write(cmd->output, " ", 1);
	}
}

int	ft_echo(t_cmd *cmd, t_global *global)
{
	int	option;
	int	i;

	option = 0;
	i = 1;
	while (cmd->val[i] != NULL && !ft_strncmp(cmd->val[i], "-n", 2)
		&& find_n(&cmd->val[i][1], 'n'))
	{
		option = 1;
		i++;
	}
	while (cmd->val[i] != NULL)
	{
		if (cmd->expand[i])
			ft_expand_echo(cmd, global, cmd->val[i]);
		else
			ft_print(cmd, i);
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}
