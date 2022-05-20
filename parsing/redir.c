/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:53:14 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/19 14:29:01 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int    main(void){
//     int fd[10];


// 	<
// 	int fd_main;
// 	char in[] = "maine.c";

// 	 fd_main = open(in, O_RDONLY);
// 	if (fd_main == -1)
// 	{
// 		perror(in);
// 		dprintf(2, "Erreur trouve avec main.c \n");
// 		return (EXIT_FAILURE);
// 	}
// 	printf("Le fd de main.c = %d\n", fd_main);
// 	close(fd_main);


// 	>
// 	int fd_out;
// 	char out[] = "out.txt";

// 	fd_out = open(out, O_WRONLY | O_CREAT, 0644);
// 	if (fd_out == -1)
// 	{
// 		perror(out);
// 		dprintf(2, "Erreur trouve avec main.c \n");
// 		return (EXIT_FAILURE);
// 	}
// 	write(fd_out, "Salut a tous les amigo", 23);
// 	printf("Le fd de %s = %d\n", out, fd_out);
// 	close(fd_out);

// 	>>
// 	int fd_out;
// 	char out[] = "append.txt";

// 	fd_out = open(out, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	if (fd_out == -1)
// 	{
// 		perror(out);
// 		dprintf(2, "Erreur trouve avec main.c \n");
// 		return (EXIT_FAILURE);
// 	}
// 	write(fd_out, "Salut a tous les amigo\n", 24);
// 	printf("Le fd de %s = %d\n", out, fd_out);
// 	close(fd_out);

// 	return (EXIT_SUCCESS);
// }d

int	redir_out(t_cmd *cmd)
{
	if (cmd->redir.fd == 1)
		cmd->redir.err = open(cmd->redir.out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		cmd->redir.err = open(cmd->redir.out, O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (cmd->redir.stdout == -1)
	{
		perror(cmd->redir.out);
		return (EXIT_FAILURE);
	}
	//close (cmd->redir.stdout);
	dup2(cmd->redir.stdout, 0);
	return (EXIT_SUCCESS);
}

// int	append_out(t_cmd *cmd)
// {
// 	cmd->redir.fd_out = open(cmd->redir.out, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	if (cmd->redir.fd_out == -1)
// 	{
// 		perror(cmd->redir.out);
// 		dprintf(2, "error\n");
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

// / 	>
// 	int fd_out;
// 	char out[] = "out.txt";

// 	fd_out = open(out, O_WRONLY | O_CREAT, 0644);
// 	if (fd_out == -1)
// 	{
// 		perror(out);
// 		dprintf(2, "Erreur trouve avec main.c \n");
// 		return (EXIT_FAILURE);
// 	}
// 	write(fd_out, "Salut a tous les amigo", 23);
// 	printf("Le fd de %s = %d\n", out, fd_out);
// 	close(fd_out);

// int	append_out(t_cmd *cmd)
// {
// 	int	fd_out;

// 	fd_out = open(cmd->redir.append_out, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	if (fd_out == -1)
// 	{
// 		perror(cmd->redir.append_out);
// 		return (EXIT_FAILURE);
// 	}
// 	printf("Le fd de %s = %d\n", cmd->redir.append_out, fd_out);
// 	close(fd_out);
// 	return (EXIT_SUCCESS);
// }
