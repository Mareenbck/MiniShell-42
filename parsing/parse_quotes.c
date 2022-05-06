/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:26:05 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/06 14:31:57 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	check_s_quotes_positon(t_token *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token->val[i])
// 	{
// 		if (is_simple_quotes(token->val[i]))
// 		{

// 		}

// 	}
// }

/*pour le plan :
	examiner si quote dans le token WORD.
	OUI ?
		si prev est un mot -> c'est une string a afficher>
		chercher la derniere quote.
		si quote % 2 == 0 la string est entre les deux
		sinon soit erreur si 1 soit elle fait partie de la string

	NON ?
		si precede d'un pipe, errror.

	si precede dun chevron
		peut etre ok.
*/
