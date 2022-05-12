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

int	ft_exit(t_global *global, t_token *token)
{
	global->exit = true;
	if (token->val == NULL)
	{
		global->exit_status = SUCCESS;
		printf("exit\n");
	}
	if (!ft_is_valid_num(token->val))
	{
		global->exit_status = 2;
		printf("exit: %s: numeric argument required\n", token->val);
		return (1);
	}
	if (ft_is_valid_num(token->val))
	{
		global->exit_status = (unsigned)ft_atoi(token->val);
		printf("exit\n");
	}
	if (token->next->val != NULL)
	{
		global->exit = false;
		global->exit_status = 1;
		printf("exit: too many arguments\n");
	}
	return (0);
}
