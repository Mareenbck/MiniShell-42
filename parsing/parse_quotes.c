/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:26:05 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/12 11:11:36 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	count_d_quotes(t_token *token)
// {
// 	int	i;
// 	int count;

// 	count = 0;
// 	while (token->token == WORD)
// 	{
// 		i = 0;
// 		while (token->val[i])
// 		{
// 			if (is_doble_quotes(token->val[i]))
// 				count++;
// 			i++;
// 		}
// 		token = token->next;
// 	}
// 	return (count);
// }

// int	count_s_quotes(t_token *token)
// {
// 	int	i;
// 	int count;

// 	count = 0;
// 	while (token->token == WORD)
// 	{
// 		i = 0;
// 		while (token->val[i])
// 		{
// 			if (is_simple_quotes(token->val[i]))
// 				count++;
// 			i++;
// 		}
// 		token = token->next;
// 	}
// 	return (count);
// }

// void	recup_count_d_quotes(t_token *token)
// {
// 	int	countd;
// 	int	counts;

// 	countd = count_d_quotes(token);
// 	counts = count_s_quotes(token);
// 	if (countd % 2 == 0 || counts % 2 == 0)
// 		trim_global_quotes(token);
// 	else
// 		ft_error("Command not found\n");
// 	printf("countd = %d\n", countd);
// }

void	parso(t_token *token, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (token->token == WORD)
	{
		j = 0;
		while (cmd->val[i][j])
		{
			while (cmd->val[i][j] && cmd->val[i][j] != '\'')
			{
				j++;
			}
			printf("coucou\n");
			token->len = j;
			cmd->val[i] = ft_strdup_bis(&cmd->val[i][j - token->len], token->len);
			j++;
			i++;
		}
		token = token->next;
	}
	printf("len = %d\n", token->len);
}
