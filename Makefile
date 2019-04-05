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

NAME = lem-in

SRC = lemin.c graph.c structs.c
LIBFT = ./libft
PRINTF = ./ft_printf
OBJ = $(SRC:.c=.o)
INC = ./
CC	= gcc
# CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)
	
$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@gcc  -I$(INC) -c $(SRC)
	@gcc $(OBJ) -L $(LIBFT) -lft -L $(PRINTF) -lftprintf -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	@rm -rf $(OBJ)
	@make clean -C $(LIBFT)
	@make clean -C $(PRINTF)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make fclean -C $(PRINTF)

re: fclean all