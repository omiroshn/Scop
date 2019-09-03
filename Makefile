NAME = scop

FILES = main init ft_strsplit math
SRC = $(addprefix src/, $(addsuffix .cpp, $(FILES)))
OBJECTS = $(addprefix obj/, $(addsuffix .o, $(FILES)))

INCLUDES = -I /Users/omiroshn/.brew/Cellar/glew/2.1.0/include \
	-I /Users/omiroshn/.brew/Cellar/glm/0.9.9.5/include \
	-I /Users/omiroshn/.brew/Cellar/sdl2/2.0.9_1/include \
	-I vendor/stb_image

LIBS = -L /Users/omiroshn/.brew/Cellar/glew/2.1.0/lib \
	-L /Users/omiroshn/.brew/Cellar/sdl2/2.0.9_1/lib

MATH_HEADERS = -I vendor/ft_math/include
MATH_LIB = ./vendor/ft_math/lib/ft_math.a

FRAMEWORKS = -lglew -framework OpenGL -lsdl2

all: $(OBJECTS)
	clang++ $(MATH_HEADERS) $(OBJECTS) $(LIBS) $(FRAMEWORKS) -o $(NAME) 

obj/%.o: src/%.cpp
	clang++ $(INCLUDES) $(MATH_HEADERS) -o $@ -c $^ -g

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
