/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:34:42 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/17 13:10:04 by emcariot         ###   ########.fr       */
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
	if (cmd->expand[i] && cmd->val[i] != NULL)
		ft_expand_echo(cmd->val[i], global);
	else
	{
		while (cmd->val[i] != NULL)
		{
			printf("%s ", cmd->val[i]);
			i++;
		}
	}

	if (!option)
		printf("\n");
	return (0);
}
