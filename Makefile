NAME		=	cub3d

LIBFT_A		=	libft.a
LIBFT_DIR	=	libft/
LIBFT		=	$(addprefix $(LIBFT_DIR), $(LIBFT_A))

CC			=	gcc
INCLUDE		=	includes
CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDE)
RM			=	rm -f

SRCS		=	main.c 			\
				modgnl_utils.c	\
				modgnl.c		\
				read_file.c		\

OBJS		=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) -L$(LIBFT_DIR) -lft -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -ltermcap $(OBJS) -o $(NAME)
			@echo "\nLinked into executable \033[0;32mcub3d\033[0m."

$(LIBFT):
			@echo "Compiling libft.a"
			@$(MAKE) bonus -s -C $(LIBFT_DIR)

.c.o:
			@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
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