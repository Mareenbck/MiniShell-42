NAME	= minishell

LIB_DIR = ./libft

LIBFT	= ./libft/libft.a

SRCS	= main.c toolbox/utils.c signal.c \
		lexerd/lexer.c lexerd/lexer_bis.c env/parse_env.c builtin/pwd.c \
		builtin/cd.c parsing/parser_plan.c builtin/env.c \
		builtin/echo.c exe/exe.c exe/parse_exe.c \
		env/init_env.c builtin/export.c builtin/unset.c \
		parsing/pipe.c append/redir.c \
		append/append.c parsing/quotes_type.c \
		parsing/parse_quotes.c parsing/parse_quotes_bis.c \
		parsing/parse_quotes_ter.c parsing/redir_syntax.c \
		append/heredoc.c env/check_env.c env/fill_env.c \
		builtin/exit.c expand/expand.c parsing/parser_plan_bis.c \
		toolbox/error.c toolbox/list_add.c toolbox/list_clear.c \
		toolbox/list_free.c expand/expand_cmd.c expand/expand_utils.c\
		toolbox/close.c toolbox/list_free_bis.c \
		parsing/parser_plan_ter.c \



OBJS	= ${SRCS:.c=.o}

RM	= rm -f

CC	= gcc

FLAGS	= -Wall -Wextra -Werror -g3

all:		${NAME}

.c.o:
		@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${LIBFT}:
			@echo "\033[35m----Building libft----"
			@make -sC ${LIB_DIR}
			@echo "OK"

${NAME}:	${OBJS} ${LIBFT}
			@echo "\033[34m----Compiling----"
			@${CC} ${FLAGS} ${OBJS} -lreadline -o ${NAME} ${LIBFT}
			@echo "OK"

clean:
			@echo "\033[31m----Cleaning libft----"
			@make clean -sC ${LIB_DIR}
			@echo "OK"
			@echo "\033[31m----Cleaning objects----"
			@${RM} ${OBJS}
			@echo "OK"

fclean:		clean
			@echo "\033[33m----Cleaning all----"
			@${RM} ${NAME}
			@${RM} ${LIBFT}
			@echo "OK"

re:			fclean all

.PHONY:		all clean fclean re
