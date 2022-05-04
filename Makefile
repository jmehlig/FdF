# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 16:19:01 by jmehlig           #+#    #+#              #
#    Updated: 2022/05/03 18:05:39 by jmehlig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS_PATH = ./srcs/

GET_NEXT_LINE_PATH = ./includes/get_next_line/

SRCS =	$(SRCS_PATH)fdf.c \
		$(SRCS_PATH)plot.c \
		$(SRCS_PATH)get_data.c \
		$(SRCS_PATH)utils.c \

GET_NEXT_LINE_SRCS =	$(GET_NEXT_LINE_PATH)get_next_line.c \
						$(GET_NEXT_LINE_PATH)get_next_line_utils.c \

LIBFT_PATH	= ./includes/libft/

CC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror -D BUFFER_SIZE=1

MLXFLAGS =		./minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

all:	target_libft $(NAME)

target_libft:
			make -C $(LIBFT_PATH)

$(NAME): target_libft
		$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(SRCS) $(GET_NEXT_LINE_SRCS) $(LIBFT_PATH)libft.a

clean:
			make clean -C $(LIBFT_PATH)

fclean_libft:
			make fclean -C $(LIBFT_PATH)

fclean:		clean fclean_libft
			$(RM) $(NAME)

re:			fclean all


