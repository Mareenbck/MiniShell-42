/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:43:07 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/20 16:36:22 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	append_in(t_cmd *cmd, char *file_name)
// {
// 	int	fd;

// 	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	if (fd == -1)
// 	{
// 		perror(file_name);
// 		return(EXIT_FAILURE);
// 	}
// 	if (cmd->input != STDIN_FILENO)
// 	{
// 		dup2(cmd->input, fd);
// 		close(fd);
// 		cmd->input = fd;
// 	}
// 	return (EXIT_SUCCESS);
// }

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
//	char	*lim;

//	lim = NULL;
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
		write(1, "here_doc>", 10);
		str = readline(STDIN_FILENO);
		str = ft_strjoin(str, "\n");
		dprintf(1, "[%s]\n", str);
		if (!ft_strncmp(lim, str, ft_strlen(lim)))
			break ;
		write(heredoc, str, ft_strlen(str));
	}
	return (heredoc);
}


