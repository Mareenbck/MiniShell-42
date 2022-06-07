/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:05:47 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/31 14:53:13 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	check_if_expand(char *str, int i, t_cmd *cmd)
{
	if (str[0] == '$' && str[1] != '\0' && str[1] != '\"')
		cmd->expand[i] = 1;
	else
		cmd->expand[i] = 0;
}

char	*new_string(char *str, char c)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!s)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
			s[j++] = str[i++];
	}
	s[j] = '\0';
	free(str);
	return (s);
}

void	delete_quotes(t_cmd *cmd, int i, int j)
{
	char	*tmp;

	if (is_simple_quotes(cmd->val[i][j]))
	{
		if (is_empty_string(cmd->val[i]))
			cmd->val[i] = ft_strdup("");
		tmp = ft_strtrim(cmd->val[i], "\'");
		free(tmp);
		tmp = ft_strtrim(cmd->val[i], "\"");
		free(cmd->val[i]);
		cmd->val[i] = new_string(tmp, '\'');
	}
	else if (is_doble_quotes(cmd->val[i][j]))
	{
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
}

void	delete_quotes_bis(t_cmd *cmd, int i)
{
	char	*tmp;

	if (start_with_simple(cmd))
	{
		if (is_empty_string(cmd->val[i]))
			cmd->val[i] = ft_strdup("");
		tmp = ft_strtrim(cmd->val[i], "\'");
		free(tmp);
		tmp = ft_strtrim(cmd->val[i], "\"");
		free(cmd->val[i]);
		cmd->val[i] = new_string(tmp, '\'');
	}
	else if (start_with_dobles(cmd))
	{
		if (is_empty_string(cmd->val[i]))
			cmd->val[i] = ft_strdup("");
		tmp = ft_strtrim(cmd->val[i], "\"\'");
		check_if_expand(tmp, i, cmd);
		if (!cmd->expand[i])
		{
			free(cmd->val[i]);
			cmd->val[i] = new_string(tmp, '\"');
			// free(tmp);
		}
		else
			free(tmp);
	}
}
