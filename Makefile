# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/02 19:46:01 by hveiled           #+#    #+#              #
#    Updated: 2021/04/30 02:24:00 by hveiled          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

LIBFT		= ./utils/libft/libft.a

2DARR		= ./utils/ft_arr/ft_arr.a

SRCS = \
		main.c \
		utils/get_envp.c \
		utils/sort_envp.c \
		utils/get_env_val.c \
		utils/set_env_val.c \
		utils/del_env_val.c \
		utils/set_termcap.c \
		utils/shell_prompt.c \
        utils/shell_prompt_utils.c \
		utils/gnl/gnl_util.c \
		utils/gnl/get_next_line.c \
		utils/history.c\
		utils/get_binary.c \
		parser/pars_line.c \
		parser/get_arg.c \
		parser/pars_utils.c \
		execute/set_fd.c \
		execute/set_pfd.c \
		execute/exec_env.c \
		execute/exec_pwd.c \
		execute/exec_exit.c \
		execute/exec_cd.c \
		execute/exec_export.c \
		execute/exec_unset.c \
		execute/exec_echo.c \
		execute/exec_redirect.c \
		execute/exec_piped_cmd.c \
		execute/exec_single_cmd.c \
		execute/exec_signal.c \
		execute/exec_bin.c \
		execute/launch.c \
		execute/ft_error.c \
		execute/execve_error.c

LIB_ARR = \
        utils/ft_arr/free_2d.c utils/ft_arr/new_2d.c \
        utils/ft_arr/add_line.c utils/ft_arr/dl_line.c \
        utils/ft_arr/add_char.c utils/ft_arr/dl_char.c \
        utils/ft_arr/make_line.c utils/ft_arr/2d_len.c

LIB_SRCS = \
        utils/libft/ft_atoi.c \
        utils/libft/ft_bzero.c \
        utils/libft/ft_calloc.c \
        utils/libft/ft_isalnum.c \
        utils/libft/ft_isalpha.c \
        utils/libft/ft_isascii.c \
        utils/libft/ft_isdigit.c \
        utils/libft/ft_isprint.c \
        utils/libft/ft_itoa.c \
        utils/libft/ft_memccpy.c \
        utils/libft/ft_memchr.c \
        utils/libft/ft_memcmp.c \
        utils/libft/ft_memcpy.c \
        utils/libft/ft_memmove.c \
        utils/libft/ft_memset.c \
        utils/libft/ft_putchar.c \
        utils/libft/ft_putchar_fd.c \
        utils/libft/ft_putendl_fd.c \
        utils/libft/ft_putnbr_fd.c \
        utils/libft/ft_putstr_fd.c \
        utils/libft/ft_split.c \
        utils/libft/ft_strchr.c \
        utils/libft/ft_strdup.c \
        utils/libft/ft_strjoin.c \
        utils/libft/ft_strlcat.c \
        utils/libft/ft_strlcpy.c \
        utils/libft/ft_strlen.c \
        utils/libft/ft_strmapi.c \
        utils/libft/ft_strncmp.c \
        utils/libft/ft_strcmp.c \
        utils/libft/ft_strnstr.c \
        utils/libft/ft_strrchr.c \
        utils/libft/ft_strtrim.c \
        utils/libft/ft_substr.c \
        utils/libft/ft_tolower.c \
        utils/libft/ft_toupper.c \

OBJS	= $(SRCS:.c=.o)

CC		= gcc
RM		= rm -f
CFLAGS		= -Wall -Wextra -Werror
TERM		= -ltermcap

			
all:		$(NAME)


$(NAME):	$(OBJS)
			$(MAKE) bonus -C utils/libft/
			$(MAKE) -C utils/ft_arr/
			$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(2DARR) $(OBJS) $(TERM)

clean:
			@$(MAKE) clean -C utils/libft/
			@$(MAKE) clean -C utils/ft_arr/
			@$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
			$(MAKE) fclean -C utils/libft/
			$(MAKE) fclean -C utils/ft_arr/
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
