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

CC = /usr/bin/clang
FILES = vec4_init vec4_geometry \
		vec3_init vec3_geometry vec3_math \
		vec2_init mat4_init mat4_mvp \
		quaternion_init

SRC = $(addprefix obj/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
INCLUDES = -I./inc
HEADERS = ./inc/ft_math.h ./inc/vecf.h ./inc/matrix.h

EOC=\033[0m
GREEN=\033[32m
RED=\033[31m

.PHONY: all clean
# .NOTPARALLEL: all $(NAME) clean fclean re 

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@/usr/bin/printf " $(RED)>$(EOC) $(GREEN)$(NAME) is ready.$(EOC)\n"
	@/usr/bin/ar rcs $(NAME) $(OBJ)
	@/usr/bin/ranlib $(NAME)

$(OBJ): obj/%.o: src/%.c $(HEADERS)
	@$(CC) -o $@ $(FLAGS) $(INCLUDES) -c $<
	@/usr/bin/printf "$(GREEN).$(EOC)"

clean:
	@/bin/rm -rf $(OBJ)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
