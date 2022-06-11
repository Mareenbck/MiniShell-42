/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:19:32 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/09 14:31:52 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_is_valid_num(char *s)
{
	int	sign;
	int	i;

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
	if (ft_atoll(s) > INT_MAX || ft_atoll(s) < INT_MIN)
		return (false);
	return (true);
}

void	if_not_valid(t_global *global, t_cmd *cmd)
{
	g_exit_status = 2;
	printf("exit: %s: numeric argument required\n", cmd->val[1]);
	ft_free_list(global);
	ft_close(global);
	exit(g_exit_status);
}

void	if_valid(t_global *global, t_cmd *cmd)
{
	g_exit_status = ft_atoi(cmd->val[1]);
	printf("exit\n");
	ft_close(global);
	ft_free_list(global);
	exit(g_exit_status);
}

int	ft_exit(t_global *global, t_cmd *cmd)
{
	global->exit = 1;
	if (cmd->val[1] == NULL)
	{
		g_exit_status = SUCCESS;
		printf("exit\n");
		return (1);
	}
	if (!ft_is_valid_num(cmd->val[1]))
		if_not_valid(global, cmd);
	if (cmd->val[2] != NULL)
	{
		global->exit = -1;
		g_exit_status = 1;
		printf("exit: too many arguments\n");
	}
	else if (ft_is_valid_num(cmd->val[1]))
		if_valid(global, cmd);
	return (global->exit);
}
