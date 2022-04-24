/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:35:25 by emcariot          #+#    #+#             */
/*   Updated: 2022/04/20 17:35:26 by emcariot         ###   ########.fr       */
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

typedef enum
{
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
  MINUS = 11,
  SPACE = 10,
} token_type;

typedef struct s_token
{
  char token;
  char *val;
  int len;
  struct s_token *next;
} t_token;

typedef struct s_global
{
	char **env;
	t_token *head;
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

typedef struct ss_list
{
	struct s_elemt	*head;
}	t_liste;


typedef struct s_elemt
{
	char	*val;
	int	pipe;
	struct s_elemt	*next;
}	t_elemt;


/* PARSING */
void	ft_exe(t_global *global, char *av);

/* UTILS */
void	**ft_free_tab(char **tab);
void	ft_error(char *msg);
t_token *lstlast(t_token *lst);
void ft_lstaddback(t_token **alst, t_token *new);
void ft_lst_clear(t_token **lst, void (*del)(void *));
char *ft_strdup_bis(const char *s1, int len);

// SIGNAL
void siginthandler();
void signalslash();

//LEXER
t_line	*fill_linked_list(char *str);
void test(t_line *line);
void	ft_test_lex(char *line, t_global *global);
t_liste	*ft_split_pipe(char *line);
void afficherListe(t_liste *list);

void init_line(char *line, t_token **head);
int ft_lex(char *str, t_token *token);

#endif
