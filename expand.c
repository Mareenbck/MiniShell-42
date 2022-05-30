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

void ft_expand_echo(t_cmd *cmd, t_global *global, char *str)
{
	t_env *env;
	char *tmp;

	env = global->head_env;
	if (cmd->val[1] != NULL && cmd->val[1][1] == '?')
		printf("%d", g_exit_status);
	else if (str[0] == '$' && !str[1])
	{
		ft_lst_clear3(&global->head_env, free);
		ft_lst_clear(&global->head, free);
		ft_lst_clear2(&global->headcmd, free);
		ft_error("Command not found2", NOTFOUND);
	}
	else
	{
		// printf("str : %s\n", str);
		env = find_name(&global->head_env, &str[1], ft_strlen(&str[1]));
		if (env)
			printf("%s\n", env->var_value);
		else if (str[1] == '\"')
		{
			tmp = ft_strtrim(str, "\"$");
			printf("%s\n", tmp);
		}
		else
		{
			// ft_lst_clear(&global->head, free);
			// ft_lst_clear2(&global->headcmd, free);
			// ft_lst_clear3(&global->head_env, free);
			ft_error("Command not found3", NOTFOUND);
		}
	}
}

void	ft_expand_cmd_first(t_global *global)
{
	t_cmd *cmd;
	char **split;
	t_env *env;
	int i;
	int j;
//SI CMD->VAL QUE 0 , PAR DARG APRES/ALORS ON SPLIT ET ON COLLE TOUT POUR VERIFIER SI CMD APPLIQUABLE OU PAS
//SINON ON FAIT EXPAND DANS FT_EXE
	cmd = global->headcmd;
	while (cmd->next)
	{
		if (!ft_strchr(cmd->val[0], '$'))
			break ;
		if (!cmd->val[1])
		{
			split = ft_split_many(cmd->val[0], "$\"");
			if (split[1] == NULL)
			{
				ft_free_tab(split);
				break ;
			}
		}
		else
			break ;
		i = 0;
		while (split[i] != NULL)
		{
			env = find_name(&global->head_env, split[i], ft_strlen(split[i]));
			if (env && i == 0)
				split[i] = env->var_value;
			else if (env && i > 0)
				split[0] = ft_strjoin(split[0], env->var_value);
			else if (i != 0)
				split[0] = ft_strjoin(split[0], split[i]);
			i++;
		}
		ft_free_tab(cmd->val);
		cmd->val = ft_split(split[0], ' ');
		j = 0;
		if (cmd->val[1] != NULL)
		{
			while (cmd->val[j])
			{
				printf("cmd : %s\n", cmd->val[j]);
				cmd->expand[j] = 0;
				j++;
			}
		}
		ft_free_tab(split);
		cmd = cmd->next;
	}
}
