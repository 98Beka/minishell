NAME = ft_arr.a

HDRS = ./

SRCS =	free_2d.c new_2d.c\
		add_line.c dl_line.c\
		add_char.c dl_char.c\
		make_line.c dl_len.c
OBJS = $(SRCS:.c=.o)

CC = gcc -Wall -Wextra -Werror
AR = @ar -rcs

%.o: %.c $(HRDS)libft.h
	$(CC) -c $< -o ${<:.c=.o} -I $(HDRS)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

tst: re
	$(CC) tst.c $(SRCS) -g
	rm -f $(OBJS)
	$(RM) $(NAME)


clean:
	rm -f $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re