/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:41 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/08 19:14:42 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_quotes_help(t_cmd *cmd, int i)
{
	char	*tmp;

	if (is_empty_string(cmd->val[i]))
		cmd->val[i] = ft_strdup("");
	tmp = ft_strtrim(cmd->val[i], "\'\"");
	printf("tmp = %s\n", tmp);
	free(cmd->val[i]);
	cmd->val[i] = new_string(tmp, '\'');
}

void	delete_quotes_help2(t_cmd *cmd, int i)
{
	char	*tmp;

	if (is_empty_string(cmd->val[i]))
			cmd->val[i] = ft_strdup("");
	tmp = ft_strtrim(cmd->val[i], "\"\'");
	check_if_expand(tmp, i, cmd);
	if (!cmd->expand[i])
	{
		if (cmd->val[i][0] == '$')
		{
			free(cmd->val[i]);
			cmd->val[i] = new_string(tmp, '\"');
			cmd->val[i] = new_string(cmd->val[i], '$');
		}
		else
		{
			free(cmd->val[i]);
			cmd->val[i] = new_string(tmp, '\"');
		}
	}
	free(tmp);
}

void	delete_quotes(t_cmd *cmd, int i, int j)
{
	if (is_simple_quotes(cmd->val[i][j]))
		delete_quotes_help(cmd, i);
	if (is_doble_quotes(cmd->val[i][j]))
		delete_quotes_help2(cmd, i);
}

void	delete_quotes_ter(t_cmd *cmd, int i)
{
	char	*tmp;

	if (is_empty_string(cmd->val[i]))
		cmd->val[i] = ft_strdup("");
	tmp = ft_strtrim(cmd->val[i], "\"");
	check_if_expand(tmp, i, cmd);
	if (!cmd->expand[i])
	{
		free(cmd->val[i]);
		cmd->val[i] = new_string(tmp, '\"');
	}
	else
		free(tmp);
}

void	delete_quotes_bis(t_cmd *cmd, int i)
{
	char	*tmp;

	if (start_with_dollar(cmd->val[i]) && (cmd->val[i][1] == '\"'))
		cmd->expand[i] = 2;
	if (start_with_simple(cmd->val[i]))
	{
		if (is_empty_string(cmd->val[i]))
			cmd->val[i] = ft_strdup("");
		tmp = ft_strtrim(cmd->val[i], "\'\"");
		free(cmd->val[i]);
		cmd->val[i] = new_string(tmp, '\'');
	}
	else if (start_with_dobles(cmd->val[i]) || cmd->expand[i] == 0)
		delete_quotes_ter(cmd, i);
}
