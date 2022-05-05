/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:15:28 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/05 15:34:53 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    expend_redir_o(t_token *token)
{
    char    *file_name;
    if (token->token == REDIR_IN)
    {
        file_name = ft_strdup(token->next->val);
    }
}