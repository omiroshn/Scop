NAME = scop

# FLAGS = -Wall -Wextra -Werror

CC = /usr/bin/clang
FILES = main \
		init \
		create_shader \
		shader_locations \
		error \
		timer \
		parse_obj \
		helpers \
		input_handler \
		bind \
		draw \
		load_obj \
		cut_string

LIBFT_DIR = libft/
MATH_DIR = ft_math/
SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJECTS = $(addprefix obj/, $(addsuffix .o, $(FILES)))

WHOAMI = $(shell whoami)

ifeq ($(WHOAMI), omiroshn)
	LOCAL_PATH = ~/.brew/Cellar/
else
	LOCAL_PATH = /usr/local/Cellar/
endif

PATH_GLEW = $(LOCAL_PATH)glew/2.1.0/
PATH_SDL = $(LOCAL_PATH)sdl2/2.0.10/

INCLUDES = -I $(PATH_GLEW)include \
	-I $(PATH_SDL)include \
	-I includes \
	-I libft/includes \
	-I libft/ft_printf/includes \
	-I ft_math/inc

LIBS = -L $(PATH_GLEW)lib \
	-L $(PATH_SDL)lib \
	$(LIBFT_DIR)libft.a \
	$(MATH_DIR)ft_math.a

FRAMEWORKS = -lglew -framework OpenGL -lsdl2

all: $(NAME)	

$(NAME): $(LIBFT_DIR)libft.a $(MATH_DIR)ft_math.a $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) $(FRAMEWORKS) -o $(NAME)

$(LIBFT_DIR)libft.a:
	@make -C $(LIBFT_DIR) -j4 --no-print-directory

$(MATH_DIR)ft_math.a:
	@make -C $(MATH_DIR) -j4 --no-print-directory

obj/%.o: src/%.c
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $^ -g

clean:
	@/bin/rm -rf $(OBJECTS)
	@make clean -C $(LIBFT_DIR) -j4 --no-print-directory
	@make clean -C $(MATH_DIR) -j4 --no-print-directory

fclean: clean
	@/bin/rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR) -j4 --no-print-directory
	@make fclean -C $(MATH_DIR) -j4 --no-print-directory

re: fclean all
