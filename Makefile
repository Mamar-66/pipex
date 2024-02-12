NAME	=	pipex
NAME_BONUS	=	pipex_bonus

CC	=	gcc

CFLAGS	=	-Wall -Werror -Wextra

SRC_PATH	=	srcs/
SRC_BONUS_PATH	=	srcs_bonus/
OBJ_PATH	=	objs/
OBJ_BONUS_PATH	=	objs_bonus/
LIBFT_PATH	=	./includes/libft/
FT_PRINTF_PATH	=	./includes/printf/

LIBFT_FILE		=	libft.a
FT_PRINTF_FILE	=	ft_printf.a

LIBFT_LIB		=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))
FT_PRINTF_LIB		=	$(addprefix $(FT_PRINTF_PATH), $(FT_PRINTF_FILE))

LIBFT_EX		=	$(LIBFT_LIB) $(CFLAGS)
FT_PRINTF_EX		=	$(FT_PRINTF_LIB) $(CFLAGS)

SRC	=			main.c \
				my_function_free.c \
\
				gest_add_argv/add_in_lst.c \
				gest_add_argv/continu_add_in_lst.c \
\
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
\
				ex_cmd/ex_cmd.c \
				ex_cmd/return_path.c \
				ex_cmd/return_path_caract.c \

SRC_BONUS	=	main.c \
				my_function_free.c \
\
				gest_add_argv/add_in_lst.c \
				gest_add_argv/continu_add_in_lst.c \
\
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
\
				ex_cmd/ex_cmd.c \
				ex_cmd/return_path.c \
				ex_cmd/return_path_caract.c \

OBJ	=	$(SRC:.c=.o)
OBJ_BONUS	= $(SRC_BONUS:.c=.o)

OBJS	=	$(addprefix $(OBJ_PATH), $(OBJ))
OBJS_BONUS	=	$(addprefix $(OBJ_BONUS_PATH), $(OBJ_BONUS))

INCS	=	-I	./includes/

all:	$(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
			mkdir $(OBJ_PATH)
			mkdir $(OBJ_PATH)/gest_add_argv
			mkdir $(OBJ_PATH)/ex_cmd
			mkdir $(OBJ_PATH)/errors
			mkdir $(OBJ_PATH)/utiles
			mkdir $(OBJ_PATH)/get_next_line

$(OBJ_BONUS_PATH)%.o:	$(SRC_BONUS_PATH)%.c
						$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_BONUS_PATH):
			mkdir $(OBJ_BONUS_PATH)
			mkdir $(OBJ_BONUS_PATH)/gest_add_argv
			mkdir $(OBJ_BONUS_PATH)/ex_cmd
			mkdir $(OBJ_BONUS_PATH)/errors
			mkdir $(OBJ_BONUS_PATH)/utiles
			mkdir $(OBJ_BONUS_PATH)/get_next_line

libft:
	@echo "\033[0;33m\nCOMPILING LIBFT$(LIBFT_PATH)\n"
	@make -sC $(LIBFT_PATH)
	@echo "\033[1;32mLIBFT created\n"

ft_printf:
	@echo "\033[0;33m\nCOMPILING FT_PRINTF$(FT_PRINTF_PATH)\n"
	@make -sC $(FT_PRINTF_PATH)
	@echo "\033[1;32mFT_PRINTF created\n"

$(NAME):	libft ft_printf ${OBJ_PATH} $(OBJS)
	@echo "\033[0;33m\nCOMPILING pipex...\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_EX) $(FT_PRINTF_EX) -o $(NAME)
	@echo "\033[1;32m ./pipex created\n"
	@rm -rf $(OBJ_BONUS_PATH)
	@rm -rf $(NAME_BONUS)

bonus: libft ft_printf $(OBJ_BONUS_PATH) $(OBJS_BONUS)
	@echo "\033[0;33m\nCOMPILING pipex bonus ...\n"
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_EX) $(FT_PRINTF_EX) -o $(NAME_BONUS)
	@echo "\033[1;32m ./pipex created\n"
	@rm -rf $(OBJ_PATH)
	@rm -rf $(NAME)

clean:
		rm -rf $(OBJ_PATH)
		rm -rf $(OBJ_BONUS_PATH)
		make -sC $(LIBFT_PATH) clean
		make -sC $(FT_PRINTF_PATH) clean

fclean:	clean
		rm -rf $(NAME)
		rm -rf $(NAME_BONUS)

re:	fclean all

.PHONY:	all clean fclean re