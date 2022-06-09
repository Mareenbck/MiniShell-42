/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:19:12 by emcariot          #+#    #+#             */
/*   Updated: 2022/06/09 17:23:24 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_init_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->val = NULL;
	new_token->len = 0;
	new_token->token = 0;
	new_token->expand = 0;
	new_token->inquotes = false;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

t_token	*create_token(char *str)
{
	t_token	*new_token;

	new_token = ft_init_token();
	new_token->token = ft_lex(str, new_token);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	init_token_list(char *line, t_token **head)
{
	int		i;
	t_token	*new;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '\0')
			break ;
		new = create_token(&line[i]);
		ft_lstaddback(head, new);
		i += new->len;
	}
	ft_lstaddback(head, ft_init_token());
}

int	ft_find_operator(char c, char c1)
{
	if (c == '>')
	{
		if (c1 == '>')
			return (APPEND_OUT);
		return (REDIR_OUT);
	}
	else if (c == '<')
	{
		if (c1 == '<')
			return (APPEND_IN);
		return (REDIR_IN);
	}
	else if (c == '\n')
		return (NEW_LINE);
	else if (c == '|')
		return (PIPE);
	else
		return (0);
}

int	ft_operator(char c)
{
	if (c != '|' && c != '>' && c != '<')
		return (0);
	else
		return (1);
}
