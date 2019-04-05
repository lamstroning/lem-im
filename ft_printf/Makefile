# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: -tdontos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/02 12:58:40 by tdontos-          #+#    #+#              #
#    Updated: 2019/01/06 13:54:10 by tdontos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = libft

SRC = ft_printf.c check_format.c save_conf.c output.c read_flags.c read_arg.c

OBJ=$(SRC:.c=.o)

CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror

all: $(NAME)

$(NAME):$(OBJ)
	@cp ../libft/libft.a $(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

fclean: clean
	@rm -f $(NAME)

re: fclean all