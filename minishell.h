/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:35:25 by emcariot          #+#    #+#             */
/*   Updated: 2022/05/04 17:42:09 by emcariot         ###   ########.fr       */
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
  REDIR_IN = 1,
  REDIR_OUT = 2,
  APPEND_OUT = 3,
  APPEND_IN = 4,
  WORD = 5,
  NEW_LINE = 6,
  PIPE = 7,
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
  int count;
  char **val;
  char *redir;
  struct s_cmd *next;
} t_cmd;

typedef struct s_env
{
  char *env;
  struct s_env *prev;
  struct s_env *next;
} t_env;

typedef struct s_global
{
	char **env;
  t_env   *head_env;
	t_token *head;
  t_cmd   *headcmd;
}	t_global;


/* PARSING */
int	count_option(char *line);
void	analize_cmd(t_token **head, t_cmd **comd);
void	ft_print_cmd(t_cmd **cmd);
t_cmd *ft_init_cmd();

// PIPE
int	check_pipe_position(t_token *token, t_cmd *cmd);

//REDIR
int check_redir_o_position(t_token *token, t_cmd *cmd);
int check_redir_i_position(t_token *token, t_cmd *cmd);
int check_append_o(t_token *token, t_cmd *cmd);
int check_append_i(t_token *token, t_cmd *cmd);

/* UTILS */
void	**ft_free_tab(char **tab);
void	ft_error(char *msg);
t_token *lstlast(t_token *lst);
void ft_lstaddback(t_token **alst, t_token *new);
void ft_lst_clear(t_token **lst, void (*del)(void *));
char *ft_strdup_bis(const char *s1, int len);
void ft_lstaddback2(t_cmd **alst, t_cmd *new);
t_cmd	*lstlast2(t_cmd *lst);
void ft_lst_clear2(t_cmd **head, void (*del)(void *));
void ft_lst_clear3(t_global *head, void (*del)(void *));


// SIGNAL
void siginthandler();
void signalslash();

//LEXER
void	ft_test_lex(char *line, t_global *global);
void init_line(char *line, t_token **head);
int ft_lex(char *str, t_token *token);

void		ft_signal(int i);
void	handle_sigint(int sig);


void	ft_execution(t_global *global, char *line);
void	ft_exe(t_global *global, char *line);
char	*search_envp(char **env, char *str);
char	**ft_split_envp(char **env);
char	*ft_join_envp(char **split_path, char *av);

// BUILTIN
int	ft_echo(t_token *token);
int	ft_pwd(void);
int	ft_cd(t_token *token, t_global *global);
int	ft_env(t_global *global);

#endif
