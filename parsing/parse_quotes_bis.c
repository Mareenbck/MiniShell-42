/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:05:47 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/27 14:28:25 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	check_if_expand(t_cmd *cmd, int i)
{
	if (cmd->val[i][0] == '$' && cmd->val[i][1] != '\0')
	{
		cmd->expand[i] = 1;
		// ft_strcpy(cmd->val[i], &cmd->val[i][1]);
	}
	else
		cmd->expand[i] = 0;
}

int	error_quotes(t_token *token)
{
	int	countd;
	int	counts;

	countd = count_d_quotes(token);
	counts = count_s_quotes(token);
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
	char *tmp;

	i = 0;
	while (cmd->val[i])
	{
		if (start_with_simple(cmd))
		{
			if (is_empty_string(cmd->val[i]))
				cmd->val[i] = ft_strdup("");
			tmp = ft_strtrim(cmd->val[i], "\'");
			tmp = ft_strtrim(cmd->val[i], "\"");
			free(cmd->val[i]);
			cmd->val[i] = new_string(tmp, '\'');
		}
		else if (start_with_dobles(cmd) || start_with_dollar(cmd))
		{
			if (is_empty_string(cmd->val[i]))
				cmd->val[i] = ft_strdup("");
			tmp = ft_strtrim(cmd->val[i], "\"");
			tmp = ft_strtrim(cmd->val[i], "\'");
			check_if_expand(cmd, i);
			free(cmd->val[i]);
			cmd->val[i] = new_string(tmp, '\"');
		}
		i++;
	}
}

int	last_call_quotes(t_cmd *cmd, t_token *token, t_global *global)
{
	// (void)global;
	if (error_quotes(token) == 1)
	{
		ft_error("Syntax error", 2);
		ft_lst_clear(&global->head, free);
		ft_lst_clear2(&global->headcmd, free);
		return (1);
	}
	else
	{
		// printf("coucou\n");
		// trim_simple_quotes(token);
		// trim_doble_quotes(token);
		delete_quotes(cmd);
	}
	return (0);
}

// export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8 ;
// echo "$A'$B"'$C"$D'$E'"$F"'"'$G'$H”
