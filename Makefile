# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 12:58:07 by rvan-aud          #+#    #+#              #
#    Updated: 2021/11/19 12:58:08 by rvan-aud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

LIBFT_A		=	libft.a
LIBFT_DIR	=	libft/
LIBFT		=	$(addprefix $(LIBFT_DIR), $(LIBFT_A))

MLX			=	mlx/libmlx.a
MLX_DIR		=	mlx/
LIB			=	-Lmlx -lz -lmlx -framework OpenGL -framework Appkit

CC			=	gcc
INCLUDE		=	includes
CFLAGS		=	-o3 -Wall -Wextra -Werror -Imlx -I$(INCLUDE)
RM			=	rm -f

SRCS_DIR	=	srcs
PARSING_DIR	=	$(SRCS_DIR)/parsing
RAYCAST_DIR	=	$(SRCS_DIR)/raycast

SRCS		=	main.c 								\
				$(SRCS_DIR)/free.c					\
				$(PARSING_DIR)/ft_strncmp_space.c	\
				$(PARSING_DIR)/get_map.c			\
				$(PARSING_DIR)/get_map_checks.c		\
				$(PARSING_DIR)/get_textures_pos.c	\
				$(PARSING_DIR)/minimap.c			\
				$(PARSING_DIR)/minimap_utils.c		\
				$(PARSING_DIR)/modgnl_utils.c		\
				$(PARSING_DIR)/modgnl.c				\
				$(PARSING_DIR)/parsing.c			\
				$(PARSING_DIR)/parsing_utils.c		\
				$(PARSING_DIR)/read_file.c			\
				$(RAYCAST_DIR)/raycast.c			\
				$(RAYCAST_DIR)/draw.c				\
				$(SRCS_DIR)/key_rotations.c			\
				$(SRCS_DIR)/key.c					\
				$(SRCS_DIR)/init.c					\

OBJS		=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(MLX) $(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(LIB) -L$(LIBFT_DIR) -lft $(OBJS) -o $(NAME)
			@echo "\nLinked into executable \033[0;32mcub3d\033[0m."

$(LIBFT):
			@echo "Compiling Libft"
			@$(MAKE) bonus -s -C $(LIBFT_DIR)

$(MLX):
			@echo "Compiling MiniLibX"
			@$(MAKE) -s -C mlx

.c.o:
			@printf "\033[0;33mGenerating $(NAME) objects... %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

localclean:
			@$(RM) $(OBJS)
			@echo "Removed object files."

clean:		localclean
			@$(MAKE) clean -s -C $(LIBFT_DIR)
			@echo "Clean libft."
			@$(MAKE) clean -s -C $(MLX_DIR)
			@echo "Clean MiniLibX."

fclean:		localclean
			@$(MAKE) fclean -s -C $(LIBFT_DIR)
			@echo "Full clean libft."
			@$(MAKE) fclean -s -C $(MLX_DIR)
			@echo "Full clean MiniLibX."
			@$(RM) $(NAME)
			@echo "Removed executable."

re:			fclean all

.PHONY:		all clean fclean localclean re
