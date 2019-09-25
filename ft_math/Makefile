# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/25 16:09:20 by omiroshn          #+#    #+#              #
#    Updated: 2019/09/25 16:09:21 by omiroshn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_math.a

FLAGS = -Wall -Wextra -Werror -Ofast

CC = clang
FILES = vec4_init vec3_init vec3_geometry vec3_math vec2_init mat4_init mat4_mvp

SRC = $(addprefix obj/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
INCLUDES = -I./inc
HEADERS = ./inc/ft_math.h ./inc/vecf.h ./inc/matrix.h

EOC=\033[0m
BLUE=\033[1;34m
YELLOW=\033[1;33m
LGREEN=\033[1;32m
GREEN=\033[32m
RED=\033[31m
LRED=\033[91m
BRED=\033[1;31m

all: $(NAME)

.PHONY: all clean
.NOTPARALLEL: all $(NAME) clean fclean re 

$(NAME): $(OBJ) $(HEADERS)
	@printf " $(RED)>$(EOC) $(GREEN)$(NAME) is ready.$(EOC)\n"
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)
$(OBJ): obj/%.o: src/%.c $(HEADERS)
	@$(CC) -o $@ $(FLAGS) $(INCLUDES) -c $<
	@printf "$(GREEN).$(EOC)"
clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all
