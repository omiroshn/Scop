/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:54:28 by omiroshn          #+#    #+#             */
/*   Updated: 2019/07/24 15:54:28 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "debug.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>

#define get_offset(type, member) ((size_t)(&((type*)(1))->member)-1)

struct Vertex
{
	glm::vec4   position;
	glm::vec3   normal;
	// glm::vec2   TexCoords;
};

int programIsRunning = 1;

SDL_Window*		InitWindow();
void			InitGlew(SDL_Window * window);

char		**ft_strsplit(char const *s, char c);
int			ft_array_length(char const *s, char c);
char		*ft_strtrim(char const *s);
void		free_strsplit(char **str);

int screen_width=960, screen_height=540;

static void		print_shader_compilation_info(const char *source, GLuint shader)
{
	GLsizei	size;
	GLchar	log[4096];

	glGetShaderInfoLog(shader, 4096, &size, log);
	printf("Shader %s\ncompilation log:\n %s\n", source, log);
}

static GLuint	create_shader(const char *source, GLenum shader_type)
{
	GLint	err;
	GLuint	shader;

	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, (const char *const *)&source, 0);
	glCompileShader(shader);
	err = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &err);
	if (err == GL_FALSE)
	{
		printf("Shader compilation failed.");
		print_shader_compilation_info(source, shader);
		glDeleteShader(shader);
		return (0);
	}
	return (shader);
}

static void		print_link_info(GLuint program)
{
	GLsizei	size;
	GLchar	log[4096];

	printf("Link stage failed.");
	glGetProgramInfoLog(program, 4096, &size, log);
	printf("Program link log:\n %s\n", log);
}

GLuint			create_program(const char *vert, const char *frag)
{
	GLuint	vert_shader;
	GLuint	frag_shader;
	GLint	programSuccess;
	GLuint	program;

	if ((vert_shader = create_shader(vert, GL_VERTEX_SHADER)) == 0 ||
		(frag_shader = create_shader(frag, GL_FRAGMENT_SHADER)) == 0)
		return (0);
	program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	glLinkProgram(program);
	programSuccess = GL_TRUE;
	glGetProgramiv(program, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		print_link_info(program);
		return (0);
	}
	GLCall( glValidateProgram(program) );
	return (program);
}


int   read_shaders(const char *vertex_path, const char *fragment_path)
{
	char    *vertex_str = NULL;
	char    *fragment_str = NULL;
	struct  stat st;
	int     v_size;
	int     f_size;
	
	const int vertex_fd = open(vertex_path, O_RDONLY);
	const int fragment_fd = open(fragment_path, O_RDONLY);
	
	stat(vertex_path, &st);
	v_size = st.st_size;
	stat(fragment_path, &st);
	f_size = st.st_size;
	
	vertex_str = (char*)malloc(v_size);
	if (read(vertex_fd, vertex_str, v_size) < 0) {
		perror("Error in reading:");
		return (false);
	}
	vertex_str[v_size] = '\0';
	
	fragment_str = (char*)malloc(f_size);
	if (read(fragment_fd, fragment_str, f_size) < 0) {
		perror("Error in reading:");
		return (false);
	}
	fragment_str[f_size] = '\0';
	
	int program;
	program = create_program(vertex_str, fragment_str);
	free(vertex_str);
	free(fragment_str);
	return (program);
}

int get_size(char **sub)
{
	int i;

	i = 1;
	while (*++sub)
		i++;
	return (i);
}

void load_obj(const char *filename, std::vector<Vertex> &vertices, std::vector<GLushort> &elements)
{
	std::ifstream in(filename, std::ios::in);
	if (!in)
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(1);
	}

	std::vector<glm::vec4> positions;
	std::vector<glm::vec3> normals;

	std::string line;
	while (getline(in, line))
	{
		if (line.substr(0,2) == "v ")
		{
			char ** sub = ft_strsplit(line.substr(2).c_str(), ' ');
			glm::vec4 v;
			v.x = std::stof(sub[0]);
			v.y = std::stof(sub[1]);
			v.z = std::stof(sub[2]);
			v.w = 1.0f;

			positions.push_back(v);
			free_strsplit(sub);
		}
		else if (line.substr(0,2) == "f ")
		{
			GLushort a,b,c;
			char *trimmed = ft_strtrim(line.substr(2).c_str());
			char **sub = ft_strsplit(trimmed, ' ');
			int size = get_size(sub);
			int i = 1;
			while (i < size - 1)
			{
				a = std::stoi(sub[0]);
				b = std::stoi(sub[i]);
				c = std::stoi(sub[i+1]);
				elements.push_back(--a);
				elements.push_back(--b);
				elements.push_back(--c);
				i++;
			}
			free_strsplit(sub);
			free(trimmed);
		}
		else if (line.substr(0,3) == "vn ")
		{
			char ** sub = ft_strsplit(line.substr(3).c_str(), ' ');
			glm::vec3 v;
			v.x = std::stof(sub[0]);
			v.y = std::stof(sub[1]);
			v.z = std::stof(sub[2]);

			normals.push_back(v);
			free_strsplit(sub);
		}
	}
	
	if (normals.empty())
	{
		normals.resize(positions.size(), glm::vec3(0.0,0.0,0.0));
		for (int i = 0; i < elements.size(); i+=3)
		{
			GLushort ia = elements[i];
			GLushort ib = elements[i+1];
			GLushort ic = elements[i+2];
			glm::vec3 normal = glm::normalize(glm::cross(
				glm::vec3(positions[ib]) - glm::vec3(positions[ia]),
				glm::vec3(positions[ic]) - glm::vec3(positions[ia])
			));
			normals[ia] = normals[ib] = normals[ic] = normal;
		}
	}

	for (int i = 0; i < elements.size(); i++)
	{
		Vertex v = {positions[i], normals[i]};
		vertices.push_back(v);
	}
}

# include <stdint.h>

uint64_t	start;
uint64_t	current;
uint64_t	current_time;
uint64_t	numer;
uint64_t	denom;
float		ttime;
float		old_time;

#include <mach/mach_time.h>

void		init_timer()
{
	mach_timebase_info_data_t coeff;

	mach_timebase_info(&coeff);
	numer = coeff.numer;
	denom = coeff.denom;
	current_time = 0;
	start = mach_absolute_time();
	current = start;
	ttime = 0.0f;
	old_time = 0.0f;
}

float delta_time = 0.0f;

void		tick()
{
	float delta_ttime;

	current = mach_absolute_time() - start;
	current_time = current * numer / denom;
	ttime = (float)(current_time / 1000) / 1000000.0f;
	delta_time = ttime - old_time;
	old_time = ttime;
}

int flags_w = 0;
int flags_a = 0;
int flags_s = 0;
int flags_d = 0;
int flags_q = 0;
int flags_e = 0;

glm::vec3 cameraPos(0.0f, 0.0f, 2.0f);
glm::vec3 cameraDir(0.0f, 0.0f, 1.0f);
glm::vec3 cameraRight(1.0f, 0.0f, 0.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

bool* keyStates = new bool[256];

void initKeys(bool *keyStates)
{
	for (int i = 0; i < 255; i++)
		keyStates[i] = false;
}

void handle_events()
{
	SDL_Event    e;
	
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			programIsRunning = 0;
		else if (e.type == SDL_KEYDOWN)
			keyStates[e.key.keysym.scancode] = true;
		else if (e.type == SDL_KEYUP)
			keyStates[e.key.keysym.scancode] = false;
		else if (e.type == SDL_MOUSEMOTION)
		{
			// if (e.motion.xrel > 0) {
			//     t_quaternion q = init_quat_deg(doom->camera.up, e.motion.xrel);
			//     doom->camera.dir = vec3_normalize(quat_transform_vec3(q, doom->camera.dir));
			//     doom->camera.right = vec3_cross(doom->camera.dir, doom->camera.up);
			// } else {
			//     t_quaternion q = init_quat_deg(doom->camera.up, e.motion.xrel);
			//     doom->camera.dir = vec3_normalize(quat_transform_vec3(q, doom->camera.dir));
			//     doom->camera.right = vec3_cross(doom->camera.dir, doom->camera.up);
			// }
			
			// if (e.motion.yrel > 0) {
			//     t_quaternion q = init_quat_deg(doom->camera.right, -e.motion.yrel);
			//     doom->camera.dir = vec3_normalize(quat_transform_vec3(q, doom->camera.dir));
			//     doom->camera.up = vec3_cross(doom->camera.right, doom->camera.dir);
			// } else {
			//     t_quaternion q = init_quat_deg(doom->camera.right, abs(e.motion.yrel));
			//     doom->camera.dir = vec3_normalize(quat_transform_vec3(q, doom->camera.dir));
			//     doom->camera.up = vec3_cross(doom->camera.right, doom->camera.dir);
			// }
		}
	}

	float cameraSpeed = delta_time * 5.f;

	if (keyStates[SDL_SCANCODE_W])
		cameraPos = cameraPos - cameraDir * cameraSpeed;
	if (keyStates[SDL_SCANCODE_S])
		cameraPos = cameraPos + cameraDir * cameraSpeed;
	if (keyStates[SDL_SCANCODE_A])
		cameraPos = cameraPos - cameraRight * cameraSpeed;
	if (keyStates[SDL_SCANCODE_D])
		cameraPos = cameraPos + cameraRight * cameraSpeed;
	if (keyStates[SDL_SCANCODE_Q])
		cameraPos = cameraPos - cameraUp * cameraSpeed;
	if (keyStates[SDL_SCANCODE_E])
		cameraPos = cameraPos + cameraUp * cameraSpeed;

	// else if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
	// {
	//     t_quaternion q = init_quat_deg(doom->camera.up, -180 * doom->timer.time);
	//     doom->camera.dir = vec3_normalize(quat_transform_vec3(q, doom->camera.dir));
	//     doom->camera.right = vec3_cross(doom->camera.dir, doom->camera.up);
	// }
	// else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
	// {
	//     t_quaternion q = init_quat_deg(doom->camera.up, 180 * doom->timer.time);
	//     doom->camera.dir = vec3_normalize(quat_transform_vec3(q, doom->camera.dir));
	//     doom->camera.right = vec3_cross(doom->camera.dir, doom->camera.up);
	// }
	// else if (e.key.keysym.scancode == SDL_SCANCODE_UP)
	// {
	//     t_quaternion q = init_quat_deg(doom->camera.right, 180 * doom->timer.time);
	//     doom->camera.dir = vec3_normalize(quat_transform_vec3(q, doom->camera.dir));
	//     doom->camera.up = vec3_cross(doom->camera.right, doom->camera.dir);
	// }
	// else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
	// {
	//     t_quaternion q = init_quat_deg(doom->camera.right, -180 * doom->timer.time);
	//     doom->camera.dir = vec3_normalize(quat_transform_vec3(q, doom->camera.dir));
	//     doom->camera.up = vec3_cross(doom->camera.right, doom->camera.dir);
	// }
}

int main (void) {

	SDL_Window * window = InitWindow();
	if (!window)
		return (-1);
	InitGlew(window);

	init_timer();
	tick();
	// delta_time = get_delta_time();
	initKeys(keyStates);

	std::vector<Vertex> vertices;
	std::vector<GLushort> elements;

	// load_obj("res/models/cube/cube.obj", vertices, elements);
	// load_obj("res/models/tree/lowpolytree.obj", vertices, elements);
	// load_obj("res/models/cat/12221_Cat_v1_l3.obj", vertices, elements);
	// load_obj("res/models/plant/plant.obj", vertices, elements);
	// load_obj("resources/42.obj", vertices, elements);
	// load_obj("resources/teapot.obj", vertices, elements);
	load_obj("resources/teapot2.obj", vertices, elements);
	
	unsigned int va, vbo_vertices, ibo_elements;

	GLCall( glGenVertexArrays(1, &va) );
	GLCall( glBindVertexArray(va) );

	GLCall( glGenBuffers(1, &vbo_vertices) );
	GLCall( glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices) );
	GLCall( glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW) );

	if (vbo_vertices == 0)
		std::cout << "vbo_vertices " << vbo_vertices << std::endl;

	GLCall( glGenBuffers(1, &ibo_elements) );
	GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements) );
	GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(elements[0]), &elements[0], GL_STATIC_DRAW) );

	if (ibo_elements == 0)
		std::cout << "ibo_elements " << ibo_elements << std::endl;

	GLCall( glEnableVertexAttribArray(0) );
	GLCall( glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0 ));
	GLCall( glEnableVertexAttribArray(1) );
	GLCall( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)get_offset(Vertex, normal) ));

	const char* vertex_shader = "res/shaders/vertex_shader.glsl";
	const char* fragment_shader = "res/shaders/fragment_shader.glsl";
	unsigned int program;
	program = read_shaders(vertex_shader, fragment_shader);

	// unsigned int textureID;
	// int m_Width, m_Height, m_BPP;
	// stbi_set_flip_vertically_on_load(1);
	// unsigned char* m_LocalBuffer = stbi_load("/Users/omiroshn/Desktop/newScop/res/textures/gold-dollar.png", &m_Width, &m_Height, &m_BPP, 4);
	// GLCall( glGenTextures(1, &textureID) );
	// GLCall( glBindTexture(GL_TEXTURE_2D, textureID) );

	// GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
	// GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
	// GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
	// GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );

	// GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer) );
	
	// GLCall( glActiveTexture(GL_TEXTURE0) );
	// GLCall( glBindTexture(GL_TEXTURE_2D, textureID) );

	// GLCall(int TextureLocation = glGetUniformLocation(program, "u_Texture"));
	// GLCall(glUniform1i(TextureLocation, 0));

	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	std::cout << size << std::endl;

	while (programIsRunning)
	{
		GLCall( glClearColor(1.0, 1.0, 1.0, 1.0) );
		GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) );


		tick();
		handle_events();
		// delta_time = get_delta_time();

		GLCall( glUseProgram(program) );

		glm::vec3 direction = cameraPos + cameraDir;

		float radius = 10.0f;
		// glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), cameraUp);
		glm::mat4 view = glm::lookAt(direction, cameraPos, cameraUp);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f * screen_width / screen_height, 0.1f, 1000.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
		glm::mat4 mvp = projection * view * model;

		GLCall(int MVPLocation = glGetUniformLocation(program, "u_MVP"));
		if (MVPLocation == -1) {
			fprintf(stderr, "Could not bind uniform %s\n", "u_MVP");
			return 0;
		}
		GLCall(glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &mvp[0][0]));

		GLCall( glBindVertexArray(va) );
		GLCall( glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, NULL) );

		SDL_GL_SwapWindow(window);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
