/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:35:32 by marinebas         #+#    #+#             */
/*   Updated: 2022/06/08 11:13:18 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\v' || c == '\n'
		|| c == '\r' || c == '\f' || c == 32)
		return (1);
	return (0);
}
