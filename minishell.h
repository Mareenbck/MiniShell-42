/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:31:26 by mbascuna          #+#    #+#             */
/*   Updated: 2022/04/20 12:16:00 by emcariot         ###   ########.fr       */
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


# define PIPE        "|"
# define SIMPLE_QUOTE    "'"
# define DOUBLE_QUOTE    """
# define DOLLAR_SIGN    "$"
# define SIMPLE_GREATER    ">"
# define DOUBLE_GREATER    ">>"
# define SIMPLE_LESS    "<"
# define DOUBLE_LESS    "<<"
# define ASSIGN        "="
# define SPACE        " "


typedef struct s_global
{
	char **env;
}	t_global;

typedef struct s_line
{
    char *val;
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

//SIGNAL
void siginthandler();
void signalslash();

//LEXER
char	*fill_linked_list(t_line *line);

#endif
