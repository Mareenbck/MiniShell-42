/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:41:37 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/13 16:09:02 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_d_quotes(t_token *token)
{
	int	i;
	int count;

	count = 0;
	while (token->token == WORD)
	{
		i = 0;
		while (token->val[i])
		{
			if (is_doble_quotes(token->val[i]))
				count++;
			i++;
		}
		token = token->next;
	}
	return (count);
}

int	count_s_quotes(t_cmd *cmd)
{
	int	i;
	int count;

	count = 0;
	i = 0;
	while (cmd->val[i])
	{
		j = 0;
		if (is_simple_quotes(cmd->val[i][j]))
			count++;
		i++;
		j++;
	}
	return (count);
}

int	start_with_simple(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->val[i])
	{
		j = 0;
		if (cmd->val[i][j] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	start_with_dobles(t_cmd *cmd)
{
	// t_cmd *cmd;
	int	i;
	int	j;

	i = 0;
	while (cmd->val[i])
	{
		j = 0;
		if (cmd->val[i][j] == '\"')
			return (1);
		i++;
	}
	return (0);
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

void	delete_quotes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->val[i])
	{
		if (start_with_simple(cmd))
		{
			cmd->val[i] = ft_strtrim(cmd->val[i], "\'");
			cmd->val[i] = new_string(cmd->val[i], '\'');

		}
		else if (start_with_dobles(cmd))
		{
			//printf("hello\n");
			printf("avant trimage = %s\n", cmd->val[i]);
			cmd->val[i] = ft_strtrim(cmd->val[i], "\"");
			printf("apres trimage = %s\n", cmd->val[i]);
			cmd->val[i] = new_string(cmd->val[i], '\"');
			printf("apres new_string = %s\n", cmd->val[i]);
		}
		i++;
	}
}

void	error_quotes(t_cmd *cmd)
{
	int	count;

	counts = count_s_quotes(cmd);
	countd = count_d_quotes(cmd);
	if (counts % 2 != 0)
		ft_error("Erreur bogoss\n");
	else if (countd % 2 != 0)
		ft_error("Erreur bogoss\n");
}
