NAME = scop

CC = gcc
FILES = main init create_shader shader_locations
# ft_strsplit    timer
LIBFT_DIR = libft/
MATH_DIR = ft_math/
SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJECTS = $(addprefix obj/, $(addsuffix .o, $(FILES)))

INCLUDES = -I /Users/omiroshn/.brew/Cellar/glew/2.1.0/include \
	-I /Users/omiroshn/.brew/Cellar/glm/0.9.9.5/include \
	-I /Users/omiroshn/.brew/Cellar/sdl2/2.0.9_1/include \
	-I vendor/stb_image \
	-I includes \
	-I libft/includes \
	-I libft/ft_printf/includes \
	-I ft_math/inc

LIBS = -L /Users/omiroshn/.brew/Cellar/glew/2.1.0/lib \
	-L /Users/omiroshn/.brew/Cellar/sdl2/2.0.9_1/lib \
	$(LIBFT_DIR)libft.a \
	$(MATH_DIR)ft_math.a

MATH_HEADERS = -I vendor/ft_math/include
MATH_LIB = ./vendor/ft_math/lib/ft_math.a

FRAMEWORKS = -lglew -framework OpenGL -lsdl2

all: $(NAME)	

$(NAME): $(LIBFT_DIR)libft.a $(MATH_DIR)ft_math.a $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) $(FRAMEWORKS) -o $(NAME)

$(LIBFT_DIR)libft.a:
	make --no-print-directory -j3 -C $(LIBFT_DIR)

$(MATH_DIR)ft_math.a:
	make --no-print-directory -j3 -C $(MATH_DIR)

obj/%.o: src/%.c
	$(CC) $(INCLUDES) -o $@ -c $^ -g

clean:
	rm -rf $(OBJECTS)
	make --no-print-directory -j3 -C $(LIBFT_DIR) clean
	make --no-print-directory -j3 -C $(MATH_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make --no-print-directory -j3 -C $(LIBFT_DIR) fclean
	make --no-print-directory -j3 -C $(MATH_DIR) fclean

re: fclean all
