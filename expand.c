/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marinebascunana <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:55:22 by marinebas         #+#    #+#             */
/*   Updated: 2022/05/21 13:55:57 by marinebas        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_expand_echo(char *str, t_global *global)
{
	t_env *env;

	env = global->head_env;
	if (str[0] == '?')
		printf("%d", g_exit_status);
	else
	{
		env = find_name(&global->head_env, str, ft_strlen(str));
		printf("%s\n", env->var_value);
	}
}

void	ft_expand_cmd_first(t_global *global)
{
	t_cmd *cmd;
	char *tmp;
	char **split;
	t_env *env;
	int i;
	// SPLIT AU DOLLAR DES LE DEBUT QUAND PLUSIEURS DOLLAR
	i = 0;
	cmd = global->headcmd;
	while (cmd->next)
	{
		// if (cmd->expand[i] && cmd->val[i] != NULL)
		// 	ft_expand_echo(cmd->val[i], global);
		tmp = ft_strchr(cmd->val[0], '$');
		// printf("tmp : %s\n", tmp);
		if (tmp)
		{
			env = find_name(&global->head_env, &tmp[1], ft_strlen(&tmp[1]));
			tmp = env->var_value;
			// printf("tmp : %s\n", tmp);
			split = ft_split(cmd->val[0], '$');
			ft_free_tab(cmd->val);
			tmp = ft_strjoin(split[0], tmp);
			ft_free_tab(split);
			cmd->val = ft_split(tmp, ' ');
			// ft_print_cmd(&global->headcmd);
			while (cmd->val[i])
			{
				cmd->expand[i] = 0;
				i++;
			}
		}
		cmd = cmd->next;
	}
}
