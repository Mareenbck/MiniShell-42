/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:35:25 by emcariot          #+#    #+#             */
/*   Updated: 2022/04/27 16:54:46 by emcariot         ###   ########.fr       */
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
  APPEND_OUT = 7,
  APPEND_IN = 8,
  WORD = 9,
  MINUS = 11,
  ISPACE = 10,
  POINT = 12,
  DOUBLE_POINT = 13,
} token_type;

typedef struct s_token
{
  char token;
  char *val;
  int len;
  struct s_token *prev;
  struct s_token *next;
} t_token;

typedef struct s_cmd
{
  char *value;
  char *infile;
  char *outfile;
  char *arg;
  char *option; //ou int bool
  struct s_cmd *next;
} t_cmd;


typedef struct s_global
{
	char **env;
	t_token *head;
  t_cmd   *headcmd;
}	t_global;


/* PARSING */
int	count_option(char *line);
void	analize_cmd(t_token **head, t_cmd **comd);
void	ft_print_cmd(t_cmd **cmd);
t_cmd *ft_init_cmd();

/* UTILS */
void	**ft_free_tab(char **tab);
void	ft_error(char *msg);
t_token *lstlast(t_token *lst);
void ft_lstaddback(t_token **alst, t_token *new);
void ft_lst_clear(t_token **lst, void (*del)(void *));
char *ft_strdup_bis(const char *s1, int len);
void ft_lstaddback2(t_cmd **alst, t_cmd *new);
t_cmd	*lstlast2(t_cmd *lst);

// SIGNAL
void siginthandler();
void signalslash();

//LEXER
void	ft_test_lex(char *line, t_global *global);


void init_line(char *line, t_token **head);
int ft_lex(char *str, t_token *token);

void		ft_signal(int i);
void	handle_sigint(int sig);

void	ft_exe(t_global *global, char *line);
#endif
