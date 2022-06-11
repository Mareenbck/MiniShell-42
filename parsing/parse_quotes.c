/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:41:37 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/08 17:59:00 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	check_if_expand(char *str, int i, t_cmd *cmd)
{
	if (str[0] == '$' && str[1] != '\0' && str[1] != '\"')
		cmd->expand[i] = 1;
	else
		cmd->expand[i] = 0;
}
