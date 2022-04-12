NAME	=	libft.a
HEAD	=	libft.h
SRCS	=	ft_strlen.c ft_memcpy.c ft_strdup.c ft_gnl.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
RM 		= 	rm -f

all: 		$(NAME)

%.o:%.c		$(HEAD)
			$(CC) $(CFLAGS) -I . -o $@ -c $<

$(NAME):	$(HEAD) $(OBJS)
			ar rcs $(NAME) $(OBJS)
			ranlib $(NAME)

clean:
			${RM} $(OBJS)

fclean:		clean
			${RM} ${NAME}

re:			fclean $(NAME)

.PHONY:		all clean fclean re
