# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/15 00:09:57 by ebaudet           #+#    #+#              #
#    Updated: 2020/08/03 04:52:07 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= RT
FILES	= env.c error.c image.c main.c rtv1.c sphere.c vector.c ray.c hook.c \
		data.c vector_calculation.c color.c light.c intersection.c plan.c \
		parse.c cylinder.c normal.c tools.c ft_scene_init.c ft_set_sphere.c \
		ft_set_plan.c ft_set_light.c ft_set_cylinder.c cone.c ft_set_cone.c \
		color_effect.c color_calculation.c pixel_color.c \
		vector_calculation2.c ft_set_ref.c random.c debug.c help.c
SRCS	= $(addprefix srcs/, $(FILES))
OBJS	= $(SRCS:srcs/%.c=.obj/%.o)
UNAME_S	:= $(shell uname -s)
MLX_DIR	?= mlx
INC		= -I libprintf/includes -I includes
FLAGS	= -Wall -Wextra -Werror
# FLAGS	=
DEBUGFLG = -fsanitize=address -g3
LIB		= libprintf/libft/libft.a -L libprintf libprintf/libftprintf.a

ifeq ($(UNAME_S),Darwin)
	INC		+= -I $(MLX_DIR) -I /usr/local/include -I /opt/homebrew/include -I /opt/X11/include
	LIBMLX	= -L $(MLX_DIR) -L /usr/local/lib -L /opt/homebrew/lib \
			  -lmlx -framework OpenGL -framework AppKit
else
	INC		+= -I /usr/X11/include -I /usr/local/include
	LIBMLX	= -L $(MLX_DIR) -L /usr/X11/lib -lmlx -lXext -lX11
endif

CC		= cc

all: $(NAME)

$(NAME): lib_comp mlx_comp create_fold_obj msg_obj $(OBJS)
	@echo "\n"
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INC) $(DEBUGFLG) $(LIB) $(LIBMLX)
	@echo "\n > \033[36m$(NAME)\033[m project compilation [\033[32mDONE\033[m]\n"

msg_obj:
	@echo "\n > \033[36m$(NAME)\033[m compiling\n"

.obj/%.o: srcs/%.c
	@$(CC) -c $< -o $@ $(FLAGS) $(INC) $(DEBUGFLG)
	@echo -n .

lib_comp:
	@echo "\n > \033[36mlibprintf\033[m compiling\n"
	@make -C libprintf

mlx_comp:
	@if [ -d "$(MLX_DIR)" ]; then \
		echo "\n > \033[36mMiniLibX\033[m compiling\n"; \
		$(MAKE) -C $(MLX_DIR); \
	else \
		echo "\n > \033[33mMiniLibX not found in $(MLX_DIR)\033[m"; \
	fi

create_fold_obj:
	@mkdir -p .obj

clean:
	@rm -rf .obj

fclean: clean
	@make fclean -C libprintf
	@make clean -C $(MLX_DIR);
	@rm -f $(NAME)
	@echo "fclean : [\033[32mDONE\033[m]"

re: fclean all

gdb: libft_comp
	cc -g $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB) $(LIBMLX)
	gdb $(NAME)

.PHONY: all libft_comp create_fold_obj clean fclean re
