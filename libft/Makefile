NAME			= libft.a

FLAGS			= -Wall -Wextra -Werror

SRCS			= ft_isalnum.c ft_isprint.c ft_isalpha.c \
				  ft_isascii.c ft_isdigit.c ft_strchr.c \
				  ft_strlcat.c ft_strlcpy.c ft_strlen.c \
				  ft_strncmp.c ft_strrchr.c ft_tolower.c \
				  ft_toupper.c ft_atoi.c ft_strdup.c \
				  ft_strnstr.c ft_memset.c ft_memcpy.c \
				  ft_memmove.c ft_bzero.c ft_memchr.c \
				  ft_memcmp.c ft_calloc.c ft_substr.c \
				  ft_strjoin.c ft_strtrim.c ft_split.c \
				  ft_itoa.c ft_strmapi.c ft_striteri.c \
				  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				  ft_putnbr_fd.c ft_sort_int_tab.c ft_atoll.c \
				  get_next_line.c ft_count_words.c ft_isspace.c \
				  ft_strcmp.c ft_sort_tab.c ft_strcat.c \
				  ft_strcpy.c ft_split_many.c ft_split_many_bis.c \
				  ft_str_isalnum.c \

BONUS			= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
				  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
				  ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS			= $(SRCS:.c=.o)
BONUS_OBJS		= $(BONUS:.c=.o)

RM				= rm -f

all:			$(NAME)

.c.o:
				gcc $(FLAGS) -c $< -o ${<:.c=.o}

$(NAME):		$(OBJS)
				ar rc $(NAME) $(OBJS)
				ranlib $(NAME)

bonus:			$(OBJS) $(BONUS_OBJS)
				ar rc $(NAME) $(OBJS) $(BONUS_OBJS)
				ranlib $(NAME)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re bonus
