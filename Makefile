# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#   Makefile                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#   By: rlossy <rlossy@student.le-101.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#   Created: 2020/05/18 10:26:09 by rlossy             #+#    #+#              #
#   Updated: 2020/05/18 10:30:33 by rlossy            ###    ########lyon.fr   #
#                                                                              #
# **************************************************************************** #

NAME		=	scop
LIB_DIR		=	./libft
SDL2_DIR	=	/Users/rlossy/.brew/Cellar/sdl2/2.0.10/
HEADER		=	./includes/
FILENAMES	=	main.c sdl.c shader.c parser.c camera.c live.c texture.c
FILENAMES   +=	events.c utils.c

SOURCES		=	$(addprefix srcs/, $(FILENAMES))
OBJECTS		=	$(addprefix build/, $(FILENAMES:.c=.o)) 

L_FT		=	$(LIB_DIR)
LIB_LNK		=	-L $(L_FT) -l ft
LIB_INC		=	-I $(L_FT)/libft.h

SDL2_FT		=	$(SDL2_DIR)
SDL2_LNK	=	$(SDL2_FT)/lib/libSDL2-2.0.0.dylib
SDL2_INC	=	-I $(SDL2_FT)/include

FLAGS		=	-Wall -Wextra -Werror -O2
FLAGX		=	-framework OpenGL -framework AppKit

LOADIR		=	./extra/Progress_Bar-for-Makefile
LOADF		=	$(LOADIR)/loading.sh

.PHONY: all clean fclean re


all: $(NAME)

clean:
	@echo "\033[31m"
	@sh $(LOADF) $(LOADIR) $@ r n $(NAME)
	@rm -rf build/
	@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\tObject Files\t\033[0m\
	\033[1m⟿ \t\033[31mDeletion Success\033[0m ✅\n"
	@$(MAKE) -C $(L_FT) clean

fclean: clean
	@echo "\033[31m"
	@sh $(LOADF) $(LOADIR) $@ r n $(NAME)
	@rm -f $(NAME)
	@printf "\n\033[1m\033[34m\t\t\t\t⥷ $(NAME)⭃\tCompiled Files\t\033[0m\
	\033[1m⟿ \t\033[31mDeletion Success\033[0m ✅\n"
	@$(MAKE) -C $(L_FT) fclean

re: 
	@$(MAKE) fclean 
	@$(MAKE) all

build: 
	@echo "\033[35m"
	@mkdir build/

$(NAME): $(OBJECTS)
	@printf "\n\033[1m\033[34m\t\t\t\t⥷ $@⭃\tObject Files\033[0m \
		\033[1m⟿ \t\033[32mCreation Success\033[0m ✅\n"
	@$(MAKE) -C $(L_FT)
	@echo "\033[42m\033[30m"
	@sh $(LOADF) $(LOADIR) $@ e n $(NAME)
	@echo "\033[0m"
	@gcc $(FLAGS) -I $(HEADER) $(OBJECTS) $(LIB_LNK) $(SDL2_LNK) $(FLAGX) -o $@
	@printf "\n\033[1m\033[34m\t\t\t\t⥷ $@⭃\tProject\t\t\033[0m \033[1m⟿  \
		\033[32mCreation Success\033[0m ✅\n"

build/%.o: srcs/%.c $(HEADER) | build
	@sh $(LOADF) $(LOADIR) $< o y
	@gcc $(FLAGS) $(LIB_INC) $(SDL2_INC) -I $(HEADER) -c $< -o $@
