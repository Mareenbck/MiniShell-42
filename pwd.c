/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbascuna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 08:57:01 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/27 08:57:13 by mbascuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A VERIFIER SI TJR OK APRES CD

void	ft_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
}
