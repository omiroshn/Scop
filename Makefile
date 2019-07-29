NAME = scop

FILES = main init ft_strsplit
SRC = $(addsuffix .cpp, $(FILES))
OBJECTS = $(addsuffix .o, $(FILES))

INCLUDES = -I /Users/omiroshn/.brew/Cellar/glfw/3.3/include \
	-I /Users/omiroshn/.brew/Cellar/glew/2.1.0/include \
	-I /Users/omiroshn/.brew/Cellar/glm/0.9.9.5/include \
	-I /Users/omiroshn/.brew/Cellar/sdl2/2.0.9_1/include \
	-I vendor/stb_image

LIBS = -L /Users/omiroshn/.brew/Cellar/glfw/3.3/lib \
	-L /Users/omiroshn/.brew/Cellar/glew/2.1.0/lib \
	-L /Users/omiroshn/.brew/Cellar/sdl2/2.0.9_1/lib

FRAMEWORKS = -lglfw -lglew -framework OpenGL -lsdl2

all: $(OBJECTS)
	clang++ $(OBJECTS) $(LIBS) $(FRAMEWORKS) -o $(NAME) 

./%.o: ./%.cpp
	clang++ $(INCLUDES) -o $@ -c $^ -g

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all