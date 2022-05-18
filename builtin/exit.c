/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:19:32 by mbascuna          #+#    #+#             */
/*   Updated: 2022/05/11 10:19:49 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_is_valid_num(char *s)
{
	int	sign;
	int i;

	i = 0;
	sign = 0;
	if (!s[i])
		return (false);
	while (s[i] == 43 || s[i] == 45)
	{
		sign++;
		i++;
	}
	while (ft_isdigit(s[i]))
		i++;
	if (sign > 1 || s[i])
		return (false);
	return (true);
}

int	ft_exit(t_global *global, t_cmd *cmd)
{
	global->exit = true;
	if (cmd->val[1] == NULL)
	{
		g_exit_status= SUCCESS;
		printf("exit\n");
		return (1);
		// ft_error("exit\n", SUCCESS);
	}
	if (!ft_is_valid_num(cmd->val[1]))
	{
		g_exit_status= 2;
		printf("exit: %s: numeric argument required\n", cmd->val[1]);
		return (1);
	}
	if (ft_is_valid_num(cmd->val[1]))
	{
		g_exit_status= ft_atoi(cmd->val[1]);
		printf("exit\n");
	}
	if (cmd->val[2] != NULL)
	{
		global->exit = false;
		g_exit_status= 1;
		printf("exit: too many arguments\n");
	}
	return (global->exit);
}
