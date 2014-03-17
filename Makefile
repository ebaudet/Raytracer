# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/15 00:09:57 by ebaudet           #+#    #+#              #
#    Updated: 2014/03/17 18:17:24 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= RT
FILES	= env.c error.c image.c main.c rtv1.c sphere.c vector.c ray.c hook.c \
		data.c vector_calculation.c color.c light.c
SRCS	= $(addprefix srcs/, $(FILES))
OBJS	= $(SRCS:srcs/%.c=.obj/%.o)
INC		= -I includes -I libft/includes
FLAGS	= -Wall -Wextra -Werror
LIB		= -L libft -lft
LIBMLX	= -L /usr/X11/lib -lmlx -lXext -lX11
CC		= cc

all: $(NAME)

$(NAME): libft_comp create_fold_obj $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB) $(LIBMLX)

.obj/%.o: srcs/%.c
	$(CC) -c $< -o $@ $(FLAGS) $(INC)

libft_comp:
	make -C libft

create_fold_obj:
	mkdir -p .obj

clean:
	rm -rf .obj

fclean: clean
	rm -f $(NAME)

re: fclean all

gdb: libft_comp
	cc -g $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB) $(LIBMLX)
	gdb $(NAME)

.PHONY: all libft_comp create_fold_obj clean fclean re
