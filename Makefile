NAME		=	cub3D

LIBFT_A		=	libft.a
LIBFT_DIR	=	libft/
LIBFT		=	$(addprefix $(LIBFT_DIR), $(LIBFT_A))

MLX			=	mlx/libmlx.a
LIB			=	-Lmlx -lz -lmlx -framework OpenGL -framework Appkit

CC			=	gcc
INCLUDE		=	includes
CFLAGS		=	-fsanitize=address -Wall -Wextra -Werror -I$(INCLUDE)
RM			=	rm -f

SRCS		=	main.c 				\
				free.c				\
				get_map.c			\
				get_textures_pos.c	\
				modgnl_utils.c		\
				modgnl.c			\
				parsing.c			\
				read_file.c			\
				raycast/raycast.c

OBJS		=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(MLX) $(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(LIB) -L$(LIBFT_DIR) -lft $(OBJS) -o $(NAME)
			@echo "\nLinked into executable \033[0;32mcub3d\033[0m."

$(LIBFT):
			@echo "Compiling libft.a"
			@$(MAKE) bonus -s -C $(LIBFT_DIR)

$(MLX):
			@echo "\n\033[0;32mCompiling MiniLibX...\033[0;33m"
			@$(MAKE) -C mlx

.c.o:
			@printf "\033[0;33mGenerating $(NAME) objects... %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

localclean:
			@$(RM) $(OBJS)
			@echo "Removed object files."

clean:		localclean
			@$(MAKE) clean -s -C $(LIBFT_DIR)
			@echo "Clean libft."

fclean:		localclean
			@$(MAKE) fclean -s -C $(LIBFT_DIR)
			@echo "Full clean libft."
			@$(RM) $(NAME)
			@echo "Removed executable."

re:			fclean all

.PHONY:		all clean fclean localclean re