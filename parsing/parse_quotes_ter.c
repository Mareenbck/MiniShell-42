/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_ter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:39:59 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/03 16:50:48 by emcariot         ###   ########.fr       */
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

int	error_quotes(t_cmd *cmd)
{
	int	countd;
	int	counts;

	countd = count_d_quotes(cmd);
	counts = count_s_quotes(cmd);
	if (counts % 2 != 0 && countd % 2 == 0 && countd >= 2)
		return (0);
	if (countd % 2 != 0 && counts % 2 == 0 && counts >= 2)
		return (0);
	if (countd % 2 != 0)
		return (1);
	else if (counts % 2 != 0)
		return (1);
	return (0);
}

void	dispatch_parsing(t_cmd *cmd)
{
	int	i;
	// int	j;

	i = 0;
	while (cmd->val[i])
	{
		// j = 0;
		// while (cmd->val[i][j])
		// {
		printf("cmd val[%d] : %s\n", i, cmd->val[i]);
		if (start_with_simple(cmd->val[i]) || start_with_dobles(cmd->val[i]) || start_with_dollar(cmd->val[i]))
		{
			delete_quotes_bis(cmd, i);
			// break ;
		}
		if (ft_strchr(cmd->val[i], '\'') && !cmd->expand[i])
			cmd->val[i] = new_string(cmd->val[i], '\'');
		if (ft_strchr(cmd->val[i], '\"') && !cmd->expand[i])
			cmd->val[i] = new_string(cmd->val[i], '\"');
		i++;
				// delete_quotes(cmd, i, j);
			// j++;
		// }
	}
}

int	last_call_quotes(t_cmd *cmd, t_token *token, t_global *global)
{
	(void)token;
	if (error_quotes(cmd) == 1)
	{
		ft_error("Syntax error", 2);
		ft_lst_clear(&global->head, free);
		ft_lst_clear2(&global->headcmd, free);
		return (1);
	}
	else
		dispatch_parsing(cmd);
	return (0);
}
