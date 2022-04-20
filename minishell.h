/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:31:26 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/20 15:52:26 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"



typedef enum {
	PIPE = 0,
	DOLLAR = 1,
	DOUBLE_QUOTE = 2,
	SIMPLE_QUOTE = 3,
	REDIR_IN = 4,
	REDIR_OUT = 5,
	ASSIGN = 6,
	// DOUBLE_GREATER = 7,
	// HEREDOC = 8,
	WORD = 9,
	// SPACE = 10
} token_type;

typedef struct s_global
{
	char **env;
	char token;
}	t_global;

typedef struct s_line
{
    char    *val;
    int     pipe;
    struct s_tmp *tmp;
    struct s_line *next;
}   t_line;

typedef struct s_tmp
{
    char *val;
    char *type;
    struct s_tmp *next;
}   t_tmp;

/* PARSING */
void	ft_exe(t_global *global, char *av);

/* UTILS */
void	**ft_free_tab(char **tab);
void	ft_error(char *msg);
t_line	*lstlast(t_line *lst);

//SIGNAL
void siginthandler();
void signalslash();

//LEXER
t_line	*fill_linked_list(char *str);
void test(t_line *line);
void	ft_test_lex(char *line, t_global *global);

#endif
