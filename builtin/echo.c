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

void ft_expand_echo(char *str, t_global *global)
{
	t_env *env;

	env = global->head_env;
	if (str[0] == '?')
		printf("%d", g_exit_status);
	else
	{
		env = find_name(&global->head_env, str, ft_strlen(str));
		printf("%s", env->var_value);
	}
}

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
	while (i < cmd->count)
	{
		while (!ft_strncmp(cmd->val[i], "-n", 2) && find_n(&cmd->val[i][1], 'n'))
		{
			option = 1;
			i++;
		}
		if (cmd->expand[i])
			ft_expand_echo(cmd->val[i], global);
		else if (cmd->val[i] != NULL)
			printf("%s ", cmd->val[i]);
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}
