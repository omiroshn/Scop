# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/31 17:20:35 by omiroshn          #+#    #+#              #
#    Updated: 2018/01/31 17:20:40 by omiroshn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -Ofast
CC = /usr/bin/clang

LIBFT = ft_atoi ft_bzero ft_countwords \
		ft_isalpha ft_isdigit ft_isprint \
		ft_itoa ft_itoa_base ft_lstnew \
		ft_lstdelone ft_lstdel ft_lstadd \
		ft_lstiter ft_lstmap ft_memset \
		ft_memcpy ft_memccpy ft_memmove \
		ft_memchr ft_memcmp ft_memalloc \
		ft_memdel ft_putchar ft_putchar_fd \
		ft_putendl ft_putendl_fd ft_putnbr_fd \
		ft_putnbr ft_putstr ft_putstr_fd \
		ft_strlen ft_strdup ft_strcpy \
		ft_strncpy ft_strcat ft_strncat \
		ft_strlcat ft_strchr ft_strrchr \
		ft_strstr ft_strnstr ft_strcmp \
		ft_strncmp ft_toupper ft_tolower \
		ft_strnew ft_strdel ft_strclr \
		ft_striter ft_striteri ft_strmap \
		ft_strmapi ft_strequ ft_strnequ \
		ft_strsub ft_strjoin ft_strtrim \
		ft_strsplit ft_atoi_base ft_isascii \
		ft_rgb_to_int ft_rgb_smooth ft_isalnum \
		ft_sort_argv ft_print_bits get_next_line \
		ft_strclen ft_strlen_safe ft_chrcnt \
		ft_array_length

LIBFT_PRINTF =  ft_printf ft_vprintf print_d print_u \
				print_o print_lo print_x print_lx \
				print_p print_ls print_s print_c \
				print_percent print_else printf_cast \
				printf_parse printf_countlength printf_isflags \
				printf_unicode printf_itoa_u

OBJ_LIBFT = $(addprefix obj/, $(addsuffix .o, $(LIBFT)))
SRC_LIBFT = $(addprefix src/, $(addsuffix .c, $(LIBFT)))
OBJ_PRINTF = $(addprefix ft_printf/obj/, $(addsuffix .o, $(LIBFT_PRINTF)))
SRC_PRINTF = $(addprefix ft_printf/src/, $(addsuffix .c, $(LIBFT_PRINTF)))

HEADERS += -I./includes
HEADERS += -I./ft_printf/includes

HEADERS_LIBFT += ./includes/libft.h
HEADERS_LIBFT += ./includes/get_next_line.h
HEADER_PRINTF = ./ft_printf/includes/ft_printf.h

EOC=\033[0m
BLUE=\033[1;34m
YELLOW=\033[1;33m
GREEN=\033[32m
RED=\033[31m

all: $(NAME)

.PHONY: all clean
# .NOTPARALLEL: all $(NAME) clean fclean re 

$(NAME): $(OBJ_LIBFT) $(OBJ_PRINTF) $(HEADERS_LIBFT) $(HEADER_PRINTF)
	@/usr/bin/printf " $(RED)>$(EOC) $(GREEN)$(NAME) is ready.$(EOC)\n"
	@/usr/bin/ar rcs $(NAME) $(OBJ_LIBFT) $(OBJ_PRINTF)
	@/usr/bin/ranlib $(NAME)

$(OBJ_LIBFT): obj/%.o: src/%.c $(HEADERS_LIBFT)
	@$(CC) -o $@ $(FLAGS) $(HEADERS) -c $<
	@/usr/bin/printf "$(BLUE).$(EOC)"

$(OBJ_PRINTF): ft_printf/obj/%.o: ft_printf/src/%.c $(HEADER_PRINTF)
	@$(CC) -o $@ $(FLAGS) $(HEADERS) -c $<
	@/usr/bin/printf "$(YELLOW).$(EOC)"

clean:
	@/bin/rm -rf $(OBJ_LIBFT) $(OBJ_PRINTF)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
