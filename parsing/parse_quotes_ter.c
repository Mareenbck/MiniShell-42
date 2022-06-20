/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_ter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:39:59 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/20 11:25:12 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_empty_string(char *str)
{
	if (is_doble_quotes(str[0])
		&& is_doble_quotes(str[1]) && ft_isspace(str[2]))
		return (1);
	else if (is_simple_quotes(str[0])
		&& is_simple_quotes(str[1]) && ft_isspace(str[2]))
		return (1);
	else
		return (0);
}

void	dispatch_parsing(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->val[i])
	{
		if (start_with_simple(cmd->val[i]) || start_with_dobles(cmd->val[i])
			|| start_with_dollar(cmd->val[i]))
			delete_quotes_bis(cmd, i);
		else if (ft_strchr(cmd->val[i], '\'') && !cmd->expand[i])
		{
			cmd->val[i] = new_string(cmd->val[i], '\'');
			cmd->val[i] = new_string(cmd->val[i], '\"');
		}
		else if (ft_strchr(cmd->val[i], '\"') && !cmd->expand[i])
		{
			cmd->val[i] = new_string(cmd->val[i], '\"');
			cmd->val[i] = new_string(cmd->val[i], '\'');
		}
		i++;
	}
}

int	utils_quotes(t_cmd *cmd)
{
	int	i;
	int	j;
	int	med;

	i = 0;
	med = 0;
	while (cmd->val[i])
	{
		j = 0;
		while (cmd->val[i][j])
		{
			if (med == 0 && cmd->val[i][j] == '\'')
				med = -1;
			else if (med == 0 && cmd->val[i][j] == '"')
				med = -2;
			else if (med == -1 && cmd->val[i][j] == '\'')
				med = 0;
			else if (med == -2 && cmd->val[i][j] == '"')
				med = 0;
			j++;
		}
		i++;
	}
	return (med);
}

int	last_call_quotes(t_global *global)
{
	t_cmd	*cmd;

	cmd = global->headcmd;
	while (cmd)
	{
		if (utils_quotes(cmd))
		{
			printf("Syntax error");
			g_exit_status = 2;
			ft_lst_clear(&global->head, free);
			ft_lst_clear2(&global->headcmd, free);
			return (1);
		}
		else
			dispatch_parsing(cmd);
		cmd = cmd->next;
	}
	return (0);
}
