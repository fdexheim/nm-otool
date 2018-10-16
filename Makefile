# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/05 13:37:20 by fdexheim          #+#    #+#              #
#    Updated: 2018/10/11 15:25:09 by fdexheim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_NM = ft_nm
NAME_OTOOL = ft_otool

all: nm otool

nm: $(NAME_NM)

otool: $(NAME_OTOOL)

$(NAME_NM): $(NM_CMD) $(NM)
	@echo "\033[1;36;mCompiling $(NAME_NM)\033[1;32;m\033[0m"
	@make -C nm/
	@cp nm/$(NAME_NM) ./

$(NAME_OTOOL): $(OTOOL_CMD) $(OTOOL)
	@echo "\033[1;36;mCompiling $(NAME_OTOOL)\033[1;32;m\033[0m"
	@make -C otool/
	@cp otool/$(NAME_OTOOL) ./

clean:
	@make clean -C nm/
	@make clean -C otool/
	@rm -f $(NAME_NM)
	@rm -f $(NAME_OTOOL)

fclean:
	@make fclean -C nm/
	@make fclean -C otool/
	@rm -f $(NAME_NM)
	@rm -f $(NAME_OTOOL)

re:		fclean all

.PHONY: all clean fclean nm otool re
