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
#include <glm/gtx/euler_angles.hpp>

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>

#include "ft_math.h"

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)

#define get_offset(type, member) ((size_t)(&((type*)(1))->member)-1)

struct Vertex
{
	glm::vec4   position;
	glm::vec3   normal;
	glm::vec2   texCoords;
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

	printf("Shaders: Link stage failed.");
	glGetProgramInfoLog(program, 4096, &size, log);
	printf("Shaders: Program link log:\n %s\n", log);
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
		perror("Shaders: Error in reading:");
		return (0);
	}
	vertex_str[v_size] = '\0';
	
	fragment_str = (char*)malloc(f_size);
	if (read(fragment_fd, fragment_str, f_size) < 0) {
		perror("Shaders: Error in reading:");
		return (0);
	}
	fragment_str[f_size] = '\0';
	
	int program;
	program = create_program(vertex_str, fragment_str);
	if (!program)
	{
		printf("Failed to read shaders\n");
		return (0);
	}
	free(vertex_str);
	free(fragment_str);
	return (program);
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

bool mRightButtonPressed = false;

glm::vec3 cameraPos(0.0f, 0.0f, 2.0f);
glm::vec3 cameraDir(0.0f, 0.0f, -1.0f);
glm::vec3 cameraRight(1.0f, 0.0f, 0.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
glm::vec3 mWorldUp(0.0f, 1.0f, 0.0f);
glm::vec3 mWorldRight(1.0f, 0.0f, 0.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);

bool* keyStates = new bool[256];

void initKeys(bool *keyStates)
{
	for (int i = 0; i < 255; i++)
		keyStates[i] = false;
}

float yaw   = 0.0f;
float pitch =  0.0f;

void print_vec3(glm::vec3 vec)
{
	std::cout << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << std::endl;
}

void print_vec4(glm::vec4 vec)
{
	std::cout << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << std::endl;
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
			// if (-e.motion.xrel < 0 || -e.motion.xrel > 0)
			// {
			// 	t_vec3 up = vec3_init(mWorldUp.x, mWorldUp.y, mWorldUp.z);
			// 	t_quaternion q = init_quat_deg(up, -e.motion.xrel * delta_time * 50);
			// 	t_vec3 dir = vec3_init(cameraDir.x, cameraDir.y, cameraDir.z);
			// 	dir = vec3_normalize(quat_transform_vec3(q, dir));
			// 	t_vec3 right = vec3_cross(dir, up);
			// 	cameraDir.x = dir.x;
			// 	cameraDir.y = dir.y;
			// 	cameraDir.z = dir.z;
			// 	cameraRight.x = right.x;
			// 	cameraRight.y = right.y;
			// 	cameraRight.z = right.z;
			// }

			// if (-e.motion.yrel < 0 || -e.motion.yrel > 0)
			// {
			// 	t_vec3 right = vec3_init(cameraRight.x, cameraRight.y, cameraRight.z);
			// 	t_quaternion q = init_quat_deg(right, -e.motion.yrel * delta_time * 50);
			// 	t_vec3 dir = vec3_init(cameraDir.x, cameraDir.y, cameraDir.z);
			// 	dir = vec3_normalize(quat_transform_vec3(q, dir));
			// 	t_vec3 up = vec3_cross(right, dir);
			// 	cameraDir.x = dir.x;
			// 	cameraDir.y = dir.y;
			// 	cameraDir.z = dir.z;
			// 	cameraUp.x = up.x;
			// 	cameraUp.y = up.y;
			// 	cameraUp.z = up.z;
			// }

			
			t_vec3 up = vec3_init(cameraUp.x, cameraUp.y, cameraUp.z);
			t_vec3 right = vec3_init(cameraRight.x, cameraRight.y, cameraRight.z);
			t_quaternion q = init_quat_deg(up, -e.motion.xrel * delta_time * 50);
			t_quaternion r = init_quat_deg(right, -e.motion.yrel * delta_time * 50);
			t_quaternion su = quat_mult_quat(q,r);
			
			t_vec3 dir = vec3_init(cameraDir.x, cameraDir.y, cameraDir.z);
			dir = quat_transform_vec3(su, dir);
			cameraDir.x = dir.x;
			cameraDir.y = dir.y;
			cameraDir.z = dir.z;
			
			right = vec3_cross(dir, up);
			cameraRight.x = right.x;
			cameraRight.y = right.y;
			cameraRight.z = right.z;

			up = vec3_cross(right, dir);
			cameraUp.x = up.x;
			cameraUp.y = up.y;
			cameraUp.z = up.z;
			
		}
	}

	float cameraSpeed = delta_time * 5.f;

	if (keyStates[SDL_SCANCODE_W])
		cameraPos += cameraDir * cameraSpeed;
	if (keyStates[SDL_SCANCODE_S])
		cameraPos -= cameraDir * cameraSpeed;
	if (keyStates[SDL_SCANCODE_A])
		cameraPos -= cameraRight * cameraSpeed;
	if (keyStates[SDL_SCANCODE_D])
		cameraPos += cameraRight * cameraSpeed;
	if (keyStates[SDL_SCANCODE_Q])
		cameraPos -= cameraUp * cameraSpeed;
	if (keyStates[SDL_SCANCODE_E])
		cameraPos += cameraUp * cameraSpeed;

	// if (keyStates[SDL_SCANCODE_LEFT])
	// {
	// 	t_vec3 up = vec3_init(cameraUp.x, cameraUp.y, cameraUp.z);
	// 	t_vec3 dir = vec3_init(cameraDir.x, cameraDir.y, cameraDir.z);
	// 	t_quaternion q = init_quat_deg(up, 180 * delta_time);
	// 	dir = vec3_normalize(quat_transform_vec3(q, dir));
	// 	t_vec3 right = vec3_cross(dir, up);
	// 	cameraDir.x = dir.x;
	// 	cameraDir.y = dir.y;
	// 	cameraDir.z = dir.z;
	// 	cameraRight.x = right.x;
	// 	cameraRight.y = right.y;
	// 	cameraRight.z = right.z;
	// }
	// if (keyStates[SDL_SCANCODE_RIGHT])
	// {
	// 	t_vec3 up = vec3_init(cameraUp.x, cameraUp.y, cameraUp.z);
	// 	t_vec3 dir = vec3_init(cameraDir.x, cameraDir.y, cameraDir.z);
	// 	t_quaternion q = init_quat_deg(up, -180 * delta_time);
	// 	dir = vec3_normalize(quat_transform_vec3(q, dir));
	// 	t_vec3 right = vec3_cross(dir, up);
	// 	cameraDir.x = dir.x;
	// 	cameraDir.y = dir.y;
	// 	cameraDir.z = dir.z;
	// 	cameraRight.x = right.x;
	// 	cameraRight.y = right.y;
	// 	cameraRight.z = right.z;
	// }
	// if (keyStates[SDL_SCANCODE_UP])
	// {
	// 	t_vec3 right = vec3_init(cameraRight.x, cameraRight.y, cameraRight.z);
	// 	t_vec3 dir = vec3_init(cameraDir.x, cameraDir.y, cameraDir.z);
	// 	t_quaternion q = init_quat_deg(right, 180 * delta_time);
	// 	dir = vec3_normalize(quat_transform_vec3(q, dir));
	// 	t_vec3 up = vec3_cross(right, dir);
	// 	cameraDir.x = dir.x;
	// 	cameraDir.y = dir.y;
	// 	cameraDir.z = dir.z;
	// 	cameraUp.x = up.x;
	// 	cameraUp.y = up.y;
	// 	cameraUp.z = up.z;
	// }
	// if (keyStates[SDL_SCANCODE_DOWN])
	// {
	// 	t_vec3 right = vec3_init(cameraRight.x, cameraRight.y, cameraRight.z);
	// 	t_vec3 dir = vec3_init(cameraDir.x, cameraDir.y, cameraDir.z);
	// 	t_quaternion q = init_quat_deg(right, -180 * delta_time);
	// 	dir = vec3_normalize(quat_transform_vec3(q, dir));
	// 	t_vec3 up = vec3_cross(right, dir);
	// 	cameraDir.x = dir.x;
	// 	cameraDir.y = dir.y;
	// 	cameraDir.z = dir.z;
	// 	cameraUp.x = up.x;
	// 	cameraUp.y = up.y;
	// 	cameraUp.z = up.z;
	// }

	// print_vec(cameraUp);

 //    if (keyStates[SDL_SCANCODE_LEFT])
	// 	yaw -= 1.f;
	// if (keyStates[SDL_SCANCODE_RIGHT])
	// 	yaw += 1.f;
	// if (keyStates[SDL_SCANCODE_UP])
	// 	pitch -= 1.f;
	// if (keyStates[SDL_SCANCODE_DOWN])
	// 	pitch += 1.f;

		// glm::vec3 front;
		// // std::cout << "yaw " << cos(ceil(degreesToRadians(yaw))) << " " << ceil(degreesToRadians(yaw)) << " " << degreesToRadians(yaw) << " " << yaw << std::endl;
	 //    front.x = sin(glm::radians(yaw)) * cos(glm::radians(-pitch));
	 //    front.y = sin(glm::radians(-pitch));
	 //    front.z = -cos(glm::radians(yaw)) * cos(glm::radians(-pitch));

	 //    // std::cout << "front " << front.x << " " << front.y << " " << front.z << std::endl;
		// cameraDir = glm::normalize(front);
	 //    cameraRight = glm::normalize(glm::cross(cameraDir, mWorldUp));
	 //    cameraUp = glm::normalize(glm::cross(cameraRight, cameraDir));
		// // std::cout << "cameraDir " << cameraDir.x << " " << cameraDir.y << " " << cameraDir.z << std::endl;
		// // std::cout << "cameraRight " << cameraRight.x << " " << cameraRight.y << " " << cameraRight.z << std::endl;
		// // std::cout << "cameraUp " << cameraUp.x << " " << cameraUp.y << " " << cameraUp.z << std::endl;
}

glm::mat4 lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 upDir)
{
	glm::vec3 forward = glm::normalize(eye - target);
	glm::vec3 left = glm::normalize(glm::cross(upDir ,forward));
	glm::vec3 up = glm::cross(forward, left);

	glm::mat4 matrix(1.0);

	matrix[0][0] = left.x;
	matrix[1][0] = left.y;
	matrix[2][0] = left.z;
	matrix[0][1] = up.x;
	matrix[1][1] = up.y;
	matrix[2][1] = up.z;
	matrix[0][2] = forward.x;
	matrix[1][2] = forward.y;
	matrix[2][2] = forward.z;

	matrix[3][0] = -left.x * eye.x - left.y * eye.y - left.z * eye.z;
	matrix[3][1] = -up.x * eye.x - up.y * eye.y - up.z * eye.z;
	matrix[3][2] = -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;

	return (matrix);
}

// glm::mat4 lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
// {
//     glm::vec3 zaxis = normalize(eye - target);    
//     glm::vec3 xaxis = normalize(cross(up, zaxis));
//     glm::vec3 yaxis = cross(zaxis, xaxis);     

//     glm::mat4 orientation(
//        xaxis[0], yaxis[0], zaxis[0], 0,
//        xaxis[1], yaxis[1], zaxis[1], 0,
//        xaxis[2], yaxis[2], zaxis[2], 0,
//          0,       0,       0,     1);

//     glm::mat4 translation(
//               1,       0,       0, 0,
//               0,       1,       0, 0, 
//               0,       0,       1, 0,
//         -eye[0], -eye[1], -eye[2], 1);

//     return orientation * translation;
// }

int ft_chrcnt(char *line, char c)
{
	int i;
	int cnt;

	cnt = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == c)
			cnt++;
	}
	return (cnt);
}

int get_size(char **sub)
{
	int i;

	i = 1;
	while (*++sub)
		i++;
	return (i);
}

void parse(std::vector<GLushort> &vertexIndices,
		std::vector<GLushort> &uvIndices,
		std::vector<GLushort> &normalIndices,
		char **sub,
		int index)
{
	GLushort a,b,c;
	int slashes = ft_chrcnt(sub[index], '/');
	if (slashes) {
		char **s1 = ft_strsplit(sub[index], '/');
		int tmp_size = ft_array_length(sub[index], '/');
		a = std::stoi(s1[0]);
		if (slashes == 1 || tmp_size == 3)
			b = std::stoi(s1[1]);
		if (slashes == 2 || tmp_size == 2)
			c = std::stoi(s1[tmp_size == 2 ? 1 : 2]);
		vertexIndices.push_back(a);
		uvIndices.push_back(b);
		normalIndices.push_back(c);
		free_strsplit(s1);
	} else {
		a = sub[index] ? std::stoi(sub[index]) : 4;
		vertexIndices.push_back(a);
	}
	std::cout << a << " ";
}

void load_obj(const char *filename, std::vector<Vertex> &vertices)
{
	std::ifstream in(filename, std::ios::in);
	if (!in)
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(1);
	}

	std::vector<glm::vec4> temp_positions;
	std::vector<glm::vec2> temp_tx;
	std::vector<glm::vec3> temp_normals;

	std::vector<GLushort> vertexIndices, uvIndices, normalIndices;

	int faces_count = 0;
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

			temp_positions.push_back(v);
			free_strsplit(sub);
		}
		else if (line.substr(0,3) == "vt ")
		{
			char ** sub = ft_strsplit(line.substr(3).c_str(), ' ');
			glm::vec2 v;
			v.x = std::stof(sub[0]);
			v.y = std::stof(sub[1]);

			temp_tx.push_back(v);
			free_strsplit(sub);
		}
		else if (line.substr(0,3) == "vn ")
		{
			char ** sub = ft_strsplit(line.substr(3).c_str(), ' ');
			glm::vec3 v;
			v.x = std::stof(sub[0]);
			v.y = std::stof(sub[1]);
			v.z = std::stof(sub[2]);

			temp_normals.push_back(v);
			free_strsplit(sub);
		}
		else if (line.substr(0,2) == "f ")
		{
			faces_count++;
			char *trimmed = ft_strtrim(line.substr(2).c_str());
			char **sub = ft_strsplit(trimmed, ' ');
			int size = get_size(sub);
			int i = 1;
			while (i < size - 1)
			{
				parse(vertexIndices, uvIndices, normalIndices, sub, 0);
				parse(vertexIndices, uvIndices, normalIndices, sub, i);
				parse(vertexIndices, uvIndices, normalIndices, sub, i+1);
				std::cout << "\n";
				i++;
			}
			free_strsplit(sub);
			free(trimmed);
		}
	}

	// if (normalIndices.empty())
	// {
	// 	printf("No normals (VN) found. Generation own normals.\n");
	// 	// normals.resize(positions.size(), glm::vec3(0.0,0.0,0.0));
	// 	for (int i = 0; i < vertexIndices.size(); i+=3)
	// 	{
	// 		GLushort ia, ib, ic;
	// 		std::cout << vertexIndices[i] << std::endl;
	// 		ia = vertexIndices[i];
	// 		ib = vertexIndices[i+1];
	// 		ic = vertexIndices[i+2];
	// 		// glm::vec3 normal = glm::normalize(glm::cross(
	// 		// 	glm::vec3(positions[ib]) - glm::vec3(positions[ia]),
	// 		// 	glm::vec3(positions[ic]) - glm::vec3(positions[ia])
	// 		// ));
	// 		// normals[ia] = normals[ib] = normals[ic] = normal;
	// 	}
	// }
	
	// if (tx.empty())
	// {
	// 	printf("No texture coordinates (VT) found.\n");
	// 	glm::vec2 text(0.0f,0.0f);
	// 	for (int i = 0; i < elements.size(); i++)
	// 	{
	// 		Vertex v = {positions[i], normals[i], text};
	// 		vertices.push_back(v);
	// 	}
	// }
	// else
	// {
	// 	for (int i = 0; i < elements.size(); i++)
	// 	{
	// 		Vertex v = {positions[i], normals[i], tx[i]};
	// 		vertices.push_back(v);
	// 	}
	// }

	std::cout << "Size: " << vertexIndices.size() << std::endl;

	for (int v = 0; v < vertexIndices.size(); v += 3)
	{
		for (unsigned int i = 0; i < 3; i += 1)
		{
			glm::vec4 vertex = temp_positions[vertexIndices[v + i] - 1];
			glm::vec3 normal = temp_normals[normalIndices[v + i] - 1];

			glm::vec2 uv;
			if (temp_tx.empty()) {
				uv = glm::vec2(0.0f,0.0f);
			} else {
				uv = temp_tx[uvIndices[v + i] - 1];
			}
			
			Vertex ver = {vertex, normal, uv};
			vertices.push_back(ver);
		}
	}
}

unsigned int bind_cubemap(std::vector<std::string> textures_faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (GLuint i = 0; i < textures_faces.size(); i++)
	{
		unsigned char *data = stbi_load(textures_faces[i].c_str(), &width, &height, &nrChannels, 4);
		if (data)
        {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
        {
            std::cout << "Cubemap texture failed to load at path: " << textures_faces[i] << std::endl;
            stbi_image_free(data);
        }
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return (textureID);
}

unsigned int bind_texture(const char *path)
{
	unsigned int textureID;
	GLCall( glGenTextures(1, &textureID) );
	GLCall( glBindTexture(GL_TEXTURE_2D, textureID) );

	int m_Width, m_Height, m_BPP;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(path, &m_Width, &m_Height, &m_BPP, 4);
	if (data)
    {
		GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data) );
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Cubemap texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
	}
	GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
	GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
	GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
	GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );
	GLCall( glBindTexture(GL_TEXTURE_2D, 0) );
	return (textureID);
}

struct Binded
{
	unsigned int vao;
	unsigned int program;
};

void draw_object(unsigned int size, unsigned int program);
void draw_skybox(unsigned int size, unsigned int program);

Binded set_up_object(std::vector<Vertex> vertices)
{
	unsigned int vao, vbo;
	GLCall( glGenVertexArrays(1, &vao) );
	GLCall( glGenBuffers(1, &vbo) );
	GLCall( glBindVertexArray(vao) );
	GLCall( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
	GLCall( glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW) );
	if (vbo == 0)
		std::cout << "vbo " << vbo << std::endl;

	GLCall( glEnableVertexAttribArray(0) );
	GLCall( glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)get_offset(Vertex, position) ));
	GLCall( glEnableVertexAttribArray(1) );
	GLCall( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)get_offset(Vertex, normal) ));
	GLCall( glEnableVertexAttribArray(2) );
	GLCall( glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)get_offset(Vertex, texCoords) ));
	unsigned int program = read_shaders(
		"res/shaders/vertex_shader.glsl",
		"res/shaders/fragment_shader.glsl");
	if (!program) {
		printf("Failed to read shaders\n");
		exit(0);
	}
	return (Binded){vao, program};
}

Binded set_up_skybox(std::vector<Vertex> vertices)
{
	unsigned int vao, vbo;
	GLCall( glGenVertexArrays(1, &vao) );
	GLCall( glGenBuffers(1, &vbo) );
	GLCall( glBindVertexArray(vao) );
	GLCall( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
	GLCall( glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW) );

	GLCall( glEnableVertexAttribArray(0) );
	GLCall( glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)get_offset(Vertex, position) ));
	unsigned int program = read_shaders(
		"res/shaders/skybox.vt.glsl",
		"res/shaders/skybox.fg.glsl");
	if (!program) {
		printf("Failed to read shaders\n");
		exit(0);
	}
	return (Binded){vao, program};
}

int main (void) {

	SDL_Window * window = InitWindow();
	if (!window)
		return (-1);
	InitGlew(window);

	init_timer();
	tick();
	initKeys(keyStates);

	std::vector<Vertex> vertices;
	// load_obj("res/models/cube/newCube.obj", vertices);
	// load_obj("res/models/cube/cube.obj", vertices);
	// load_obj("res/models/tree/lowpolytree.obj", vertices);
	// load_obj("res/models/cat/12221_Cat_v1_l3.obj", vertices);
	// load_obj("res/models/earth/earth.obj", vertices);
	load_obj("res/models/penguin/PenguinBaseMesh.obj", vertices);
	// load_obj("res/models/Notebook/Lowpoly_Notebook_2.obj", vertices);
	// load_obj("res/models/plant/plant.obj", vertices);
	// load_obj("res/models/42/42.obj", vertices);
	// load_obj("res/models/teapot/teapot.obj", vertices);
	// load_obj("res/models/teapot/teapot2.obj", vertices);

	Binded bindedObj = set_up_object(vertices);

	std::vector<Vertex> skyboxVertices;
	load_obj("res/models/cube/newCube.obj", skyboxVertices);
	Binded cubemapObj = set_up_skybox(skyboxVertices);

	// const char *path = "res/models/cube/ramsey.jpg";
	// const char *path = "res/models/Notebook/textures/Lowpoly_Laptop_2.jpg";
	// const char *path = "res/models/cat/Cat_diffuse.jpg";
	// const char *path = "res/models/earth/4096_earth.jpg";
	const char* path = "res/models/penguin/Penguin_Diffuse_Color.png";
	const char *vinit[] = {
		"res/models/skybox/right.jpg",
		"res/models/skybox/left.jpg",
		"res/models/skybox/bottom.jpg",
		"res/models/skybox/top.jpg",
		"res/models/skybox/front.jpg",
		"res/models/skybox/back.jpg",
	};
	std::vector<std::string> textures_faces(vinit, std::end(vinit));

	unsigned int objectTextureID = bind_texture(path);
	unsigned int skyboxTextureID = bind_cubemap(textures_faces);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));

	while (programIsRunning)
	{
		GLCall(glClearColor(1.0, 1.0, 1.0, 1.0));
		GLCall(glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		tick();
		handle_events();

		
		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall( glBindVertexArray(cubemapObj.vao) );
		GLCall( glActiveTexture(GL_TEXTURE0) );
		GLCall( glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID) );
		draw_skybox(skyboxVertices.size(), cubemapObj.program);
		glBindVertexArray(0);

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glBindVertexArray(bindedObj.vao));
		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glBindTexture(GL_TEXTURE_2D, objectTextureID));
		draw_object(vertices.size(), bindedObj.program);
		glBindVertexArray(0);

		

		SDL_GL_SwapWindow(window);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}

void draw_skybox(unsigned int size, unsigned int program)
{
	glm::mat4 view = glm::mat4(glm::mat3(glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp)));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f * screen_width / screen_height, 0.1f, 100.0f);
	glm::mat4 mvp = projection * view;

	GLCall(glDepthFunc(GL_LEQUAL));
	GLCall(glUseProgram(program));
	GLCall(int MVPLocation = glGetUniformLocation(program, "u_MVP"));
	if (MVPLocation == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", "u_MVP");
		exit(0);
	}
	GLCall(glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &mvp[0][0]));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
	GLCall(glBindVertexArray(0));
	GLCall(glDepthFunc(GL_LESS));
}

glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -0.5, -2.0));

void draw_object(unsigned int size, unsigned int program)
{
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f * screen_width / screen_height, 0.1f, 1000.0f);	
	model = glm::rotate(model, delta_time * glm::radians(55.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
	glm::mat4 mvp = projection * view * model;

	GLCall(glUseProgram(program));
	GLCall(int MVPLocation = glGetUniformLocation(program, "u_MVP"));
	if (MVPLocation == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", "u_MVP");
		exit(0);
	}
	GLCall(glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &mvp[0][0]));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
}