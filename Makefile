NAME = scop

CC = gcc
FILES = main init create_shader shader_locations
LIBFT_DIR = libft/
MATH_DIR = ft_math/
SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJECTS = $(addprefix obj/, $(addsuffix .o, $(FILES)))

WHOAMI = $(shell whoami)

ifeq ($(WHOAMI), omiroshn)
	PATH = ~/.brew/Cellar/
	PATH_GLEW = $(PATH)glew/2.1.0/
	PATH_SDL = $(PATH)sdl2/2.0.9_1/
else
	PATH = /usr/local/Cellar/
	PATH_GLEW = $(PATH)glew/2.1.0/
	PATH_SDL = $(PATH)sdl2/2.0.10/
endif

INCLUDES = -I $(PATH_GLEW)include \
	-I $(PATH_SDL)include \
	-I vendor/stb_image \
	-I includes \
	-I libft/includes \
	-I libft/ft_printf/includes \
	-I ft_math/inc

LIBS = -L $(PATH_GLEW)lib \
	-L $(PATH_SDL)lib \
	$(LIBFT_DIR)libft.a \
	$(MATH_DIR)ft_math.a

MATH_HEADERS = -I vendor/ft_math/include
MATH_LIB = ./vendor/ft_math/lib/ft_math.a

FRAMEWORKS = -lglew -framework OpenGL -lsdl2

all: $(NAME)	

$(NAME): $(LIBFT_DIR)libft.a $(MATH_DIR)ft_math.a $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) $(FRAMEWORKS) -o $(NAME)

$(LIBFT_DIR)libft.a:
	make -C -j4 --no-print-directory $(LIBFT_DIR)

$(MATH_DIR)ft_math.a:
	make -C -j4 --no-print-directory $(MATH_DIR)

obj/%.o: src/%.c
	$(CC) $(INCLUDES) -o $@ -c $^ -g

clean:
	rm -rf $(OBJECTS)
	make clean -C -j4 --no-print-directory $(LIBFT_DIR)
	make clean -C -j4 --no-print-directory $(MATH_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C -j4 --no-print-directory $(LIBFT_DIR)
	make fclean -C -j4 --no-print-directory $(MATH_DIR)

re: fclean all
