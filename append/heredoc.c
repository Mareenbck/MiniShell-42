/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:43:07 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/24 14:32:51 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    check_lim(char *lim)
{
    int    i;

    i = -1;
    while (lim[++i])
        if (!ft_isalpha(lim[i]))
            return (1);
    return (0);
}

int	ft_heredoc(char *lim)
{
	int	heredoc;
	char	*str;

	if (check_lim(lim) != 0)
		return (EXIT_FAILURE);
	heredoc = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc == -1)
	{
		perror("here_doc ntm");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		write(1, ">", 1);
		str = readline(STDIN_FILENO);
		str = ft_strjoin(str, "\n");
		if (!ft_strncmp(lim, str, ft_strlen(lim)))
			break ;
		write(heredoc, str, ft_strlen(str));
	}
	return (heredoc);
}

