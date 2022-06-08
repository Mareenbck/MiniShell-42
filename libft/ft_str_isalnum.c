/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalnum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <mbascuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:55:45 by mbascuna          #+#    #+#             */
/*   Updated: 2022/06/08 11:58:22 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_str_isalnum(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	if (str[i] == '\0')
		return (true);
	else
		return (false);
}
