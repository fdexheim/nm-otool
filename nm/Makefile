# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2018/10/10 15:47:06 by fdexheim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

INCLUDES_PATH = ./inc/

SRC_PATH = ./src/
SRC_NAME = calc_effective_letter.c check.c check_ar.c check_ar_objects.c \
		   check_arch.c check_fat.c check_lc_tab.c \
		   check_lc_seg.c check_macho.c check_symtab.c \
		   display.c flip.c get_section_from_number.c \
		   getcmds.c handle.c handle_ar.c handle_ar_sorted.c \
		   handle_ar_object.c handle_ar_utils.c handle_arch.c handle_fat.c \
		   handle_macho.c \
		   handle_symtab.c main.c nm.c parse_nm.c \
		   print_full_number.c symbol_list.c symbol_list_add.c \
		   symbols_compare.c \
		   utils_env.c \
		   utils_env2.c utils_env_file.c utils_nbr.c utils_nbr2.c \
		   utils_str.c utils_str2.c \

OBJ_PATH = ./obj/
OBJ_NAME =	$(SRC_NAME:.c=.o)

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "\033[1;32;m[$@]\033[0m : " | tr -d '\n'
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CC_FLAGS) -I $(INCLUDES_PATH) -o $@ -c $<

$(NAME): $(OBJ)
	@$(CC) $(CC_FLAGS) -o $@ $(OBJ)
	@echo "\033[1;32;m[Compilation Successful]\033[0m"
	@echo "\033[1;36;m$(NAME)\033[1;32;m ready to go !\033[0m"

clean:
	@echo "\033[0;33;m[Clean]\033[0m              : " | tr -d '\n'
	rm -f $(OBJ)

fclean:		clean
	@echo "\033[0;31;m[Deleting $(NAME)]\033[0m : " | tr -d '\n'
	rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re:			fclean all

.PHONY:		all clean fclean re
