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

#include "scop.h"
// #include "debug.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int programIsRunning = 1;
int screen_width = 960, screen_height = 540;
int space_pressed = 1;
int primitive_mode = 1;
int mode = 1;

// bool mRightButtonPressed = false;


// t_vec3 mWorldUp(0.0f, 1.0f, 0.0f);
// t_vec3 mWorldRight(1.0f, 0.0f, 0.0f);
// t_vec3 cameraFront(0.0f, 0.0f, -1.0f);




// float yaw   = 0.0f;
// float pitch =  0.0f;

// void print_vec4(glm::vec4 vec)
// {
// 	std::cout << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << std::endl;
// }

float _pitch = 0;
float _yaw = 0;

void handle_events(t_scop *s)
{
	SDL_Event    e;
	
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			programIsRunning = 0;
		else if (e.type == SDL_KEYDOWN)
		{
			s->key_states[e.key.keysym.scancode] = 1;
			if (e.key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET)
				--mode < 1 ? mode = 6 : 0;
			if (e.key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET)
				++mode > 6 ? mode = 1 : 0;
			if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
				space_pressed ^= 1;
			if (e.key.keysym.scancode == SDL_SCANCODE_P)
				primitive_mode ^= 1;
		}
		else if (e.type == SDL_KEYUP)
			s->key_states[e.key.keysym.scancode] = 0;
		else if (e.type == SDL_MOUSEMOTION)
		{
			// float mouseX = (float)e.motion.x;
   //          float mouseY = (float)e.motion.y;
			// const float mouseX_Sensitivity = 0.25f;
			// const float mouseY_Sensitivity = 0.25f;

			// int tmpX, tmpY;
			// SDL_GetMouseState (&tmpX, &tmpY);       // Mouse coords: [0,0] = top,left.
			// _pitch += mouseY_Sensitivity * tmpY;  // mouse down:  -offset → reduce (add -).
			// _yaw   += mouseY_Sensitivity * tmpX;  // mouse right: -offset → reduce (add -).
   //  		printf("%.0f %.0f\n", _yaw , _pitch);

   //  		if (_pitch >  90.0f) _pitch =  90.0f;
   //  		if (_pitch < -90.0f) _pitch = -90.0f;
   //  		if (_yaw  < -180.0f) _yaw  += 360.0f;
   //  		if (_yaw  >  180.0f) _yaw  -= 360.0f;

   //  		t_mat4 rotate = mat4_rotate(s->camera, vec3_init(-1.0f, 0.0f, 0.0f), _pitch);
			// s->camera = mat4_mul_mat4(s->camera, rotate);
			// rotate = mat4_rotate(s->camera, vec3_init(0.0f, -1.0f, 0.0f), _yaw);
			// s->camera = mat4_mul_mat4(s->camera, rotate);

			// t_vec3 up = vec3_init(s->camera.up.x, s->camera.up.y, s->camera.up.z);
			// t_vec3 right = vec3_init(s->camera.right.x, s->camera.right.y, s->camera.right.z);
			// t_quaternion q = quat_init_deg(up, -e.motion.xrel * s->timer.delta_time * 50);
			// t_quaternion r = quat_init_deg(right, -e.motion.yrel * s->timer.delta_time * 50);
			// t_quaternion su = quat_mult_quat(q,r);
			
			// t_vec3 dir = vec3_init(s->camera.direction.x, s->camera.direction.y, s->camera.direction.z);
			// dir = quat_transform_vec3(su, dir);
			// s->camera.direction.x = dir.x;
			// s->camera.direction.y = dir.y;
			// s->camera.direction.z = dir.z;
			
			// right = vec3_cross(dir, up);
			// s->camera.right.x = right.x;
			// s->camera.right.y = right.y;
			// s->camera.right.z = right.z;

			// up = vec3_cross(right, dir);
			// s->camera.up.x = up.x;
			// s->camera.up.y = up.y;
			// s->camera.up.z = up.z;
			
		}
	}


	float cameraSpeed = s->timer.delta_time * 5.f;

	
	/* camera movement */
	if (s->key_states[SDL_SCANCODE_W])
		s->camera.position = vec3_add(s->camera.position, vec3_mult_scalar(s->camera.direction, cameraSpeed));
	if (s->key_states[SDL_SCANCODE_S])
		s->camera.position = vec3_sub(s->camera.position, vec3_mult_scalar(s->camera.direction, cameraSpeed));
	if (s->key_states[SDL_SCANCODE_A])
		s->camera.position = vec3_sub(s->camera.position, vec3_mult_scalar(s->camera.right, cameraSpeed));
	if (s->key_states[SDL_SCANCODE_D])
		s->camera.position = vec3_add(s->camera.position, vec3_mult_scalar(s->camera.right, cameraSpeed));
	if (s->key_states[SDL_SCANCODE_Q])
		s->camera.position = vec3_sub(s->camera.position, vec3_mult_scalar(s->camera.up, cameraSpeed));
	if (s->key_states[SDL_SCANCODE_E])
		s->camera.position = vec3_add(s->camera.position, vec3_mult_scalar(s->camera.up, cameraSpeed));

	// /* light movement */
	// if (s->key_states[SDL_SCANCODE_UP])
	// 	s->light.position += s->camera.direction * cameraSpeed;
	// if (s->key_states[SDL_SCANCODE_DOWN])
	// 	s->light.position -= s->camera.direction * cameraSpeed;
	// if (s->key_states[SDL_SCANCODE_RIGHT])
	// 	s->light.position += s->camera.right * cameraSpeed;
	// if (s->key_states[SDL_SCANCODE_LEFT])
	// 	s->light.position -= s->camera.right * cameraSpeed;
	// if (s->key_states[SDL_SCANCODE_O])
	// 	s->light.position += s->camera.up * cameraSpeed;
	// if (s->key_states[SDL_SCANCODE_P])
	// 	s->light.position -= s->camera.up * cameraSpeed;
		

	// if (s->key_states[SDL_SCANCODE_LEFT])
	// {
	// 	t_vec3 up = vec3_init(s->camera.up.x, s->camera.up.y, s->camera.up.z);
	// 	t_vec3 dir = vec3_init(s->camera.direction.x, s->camera.direction.y, s->camera.direction.z);
	// 	t_quaternion q = quat_init_deg(up, 180 * s->timer.delta_time);
	// 	dir = vec3_normalize(quat_transform_vec3(q, dir));
	// 	t_vec3 right = vec3_cross(dir, up);
	// 	s->camera.direction.x = dir.x;
	// 	s->camera.direction.y = dir.y;
	// 	s->camera.direction.z = dir.z;
	// 	s->camera.right.x = right.x;
	// 	s->camera.right.y = right.y;
	// 	s->camera.right.z = right.z;
	// }
	// if (s->key_states[SDL_SCANCODE_RIGHT])
	// {
	// 	t_vec3 up = vec3_init(s->camera.up.x, s->camera.up.y, s->camera.up.z);
	// 	t_vec3 dir = vec3_init(s->camera.direction.x, s->camera.direction.y, s->camera.direction.z);
	// 	t_quaternion q = quat_init_deg(up, -180 * s->timer.delta_time);
	// 	dir = vec3_normalize(quat_transform_vec3(q, dir));
	// 	t_vec3 right = vec3_cross(dir, up);
	// 	s->camera.direction.x = dir.x;
	// 	s->camera.direction.y = dir.y;
	// 	s->camera.direction.z = dir.z;
	// 	s->camera.right.x = right.x;
	// 	s->camera.right.y = right.y;
	// 	s->camera.right.z = right.z;
	// }
	// if (s->key_states[SDL_SCANCODE_UP])
	// {
	// 	t_vec3 right = vec3_init(s->camera.right.x, s->camera.right.y, s->camera.right.z);
	// 	t_vec3 dir = vec3_init(s->camera.direction.x, s->camera.direction.y, s->camera.direction.z);
	// 	t_quaternion q = quat_init_deg(right, 180 * s->timer.delta_time);
	// 	dir = vec3_normalize(quat_transform_vec3(q, dir));
	// 	t_vec3 up = vec3_cross(right, dir);
	// 	s->camera.direction.x = dir.x;
	// 	s->camera.direction.y = dir.y;
	// 	s->camera.direction.z = dir.z;
	// 	s->camera.up.x = up.x;
	// 	s->camera.up.y = up.y;
	// 	s->camera.up.z = up.z;
	// }
	// if (s->key_states[SDL_SCANCODE_DOWN])
	// {
	// 	t_vec3 right = vec3_init(s->camera.right.x, s->camera.right.y, s->camera.right.z);
	// 	t_vec3 dir = vec3_init(s->camera.direction.x, s->camera.direction.y, s->camera.direction.z);
	// 	t_quaternion q = quat_init_deg(right, -180 * s->timer.delta_time);
	// 	dir = vec3_normalize(quat_transform_vec3(q, dir));
	// 	t_vec3 up = vec3_cross(right, dir);
	// 	s->camera.direction.x = dir.x;
	// 	s->camera.direction.y = dir.y;
	// 	s->camera.direction.z = dir.z;
	// 	s->camera.up.x = up.x;
	// 	s->camera.up.y = up.y;
	// 	s->camera.up.z = up.z;
	// }

	// 	// print_vec(cameraUp);

//  //    if (keyStates[SDL_SCANCODE_LEFT])
// 	// 	yaw -= 1.f;
// 	// if (keyStates[SDL_SCANCODE_RIGHT])
// 	// 	yaw += 1.f;
// 	// if (keyStates[SDL_SCANCODE_UP])
// 	// 	pitch -= 1.f;
// 	// if (keyStates[SDL_SCANCODE_DOWN])
// 	// 	pitch += 1.f;

// 		// glm::vec3 front;
// 		// // std::cout << "yaw " << cos(ceil(degreesToRadians(yaw))) << " " << ceil(degreesToRadians(yaw)) << " " << degreesToRadians(yaw) << " " << yaw << std::endl;
// 	 //    front.x = sin(glm::radians(yaw)) * cos(glm::radians(-pitch));
// 	 //    front.y = sin(glm::radians(-pitch));
// 	 //    front.z = -cos(glm::radians(yaw)) * cos(glm::radians(-pitch));

// 	 //    // std::cout << "front " << front.x << " " << front.y << " " << front.z << std::endl;
// 		// cameraDir = glm::normalize(front);
// 	 //    cameraRight = glm::normalize(glm::cross(cameraDir, mWorldUp));
// 	 //    cameraUp = glm::normalize(glm::cross(cameraRight, cameraDir));
// 		// // std::cout << "cameraDir " << cameraDir.x << " " << cameraDir.y << " " << cameraDir.z << std::endl;
// 		// // std::cout << "cameraRight " << cameraRight.x << " " << cameraRight.y << " " << cameraRight.z << std::endl;
// 		// // std::cout << "cameraUp " << cameraUp.x << " " << cameraUp.y << " " << cameraUp.z << std::endl;
// }
}

int	ft_array_length(char const *s, char c)
{
	unsigned int len;

	len = 0;
	while (*s)
	{
		if (*s == c)
			++s;
		else
		{
			++len;
			while (*s && *s != c)
				++s;
		}
	}
	return (len);
}

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

void	free_strsplit(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void parse(GLushort *vertexIndices, GLushort *uvIndices, GLushort *normalIndices, char *line, int index)
{
	GLushort	a;
	GLushort	b;
	GLushort	c;
	int			slashes;

	slashes = ft_chrcnt(line, '/');
	if (slashes)
	{
		char **s1 = ft_strsplit(line, '/');
		int tmp_size = ft_array_length(line, '/');
		a = atoi(s1[0]);
		if (slashes == 1 || tmp_size == 3)
			b = atoi(s1[1]);
		if (slashes == 2 || tmp_size == 2)
			c = atoi(s1[tmp_size == 2 ? 1 : 2]);
		vertexIndices[index] = a;
		uvIndices[index] = b;
		normalIndices[index] = c;
		free_strsplit(s1);
	}
	else
	{
		a = line ? atoi(line) : 4;
		vertexIndices[index] = a;
	}
	// ft_printf("%d ", a);
}

// создать 3 массива под величины
// записать их в 1
// затосовать
// записать в 1 и вернуть

// или записывать сразу в 1

int get_size_of_obj(char *filename)
{
	int		fd;
	int		faces_count;
	char	*line;

	ft_printf("Reading: %s\n", filename);
	if ((fd = open(filename, O_RDONLY)) < 0 || read(fd, NULL, 0) < 0)
		put_error("Failed to open file.");
	faces_count = 0;
	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp(line, "f ", 2)))
		{
			char *cutted = ft_strsub(line, 2, ft_strlen(line));
			char *trimmed = ft_strtrim(cutted);
			char **sub = ft_strsplit(trimmed, ' ');
			int i = 1;
			while (i++ < get_size(sub) - 1)
				faces_count += 3;
			free(cutted);
			free_strsplit(sub);
			free(trimmed);
		}
		free(line);
	}
	close(fd);
	return (faces_count);
}

void load_obj(t_timer *timer, const char *filename, t_vertex *vertices, int size)
{
	int		fd;
	char 	*line;
	char	**sub;
	char	*cutted;

	fd = open(filename, O_RDONLY);

	GLushort *vertexIndices = ft_memalloc(sizeof(GLushort) * size);
	GLushort *uvIndices = ft_memalloc(sizeof(GLushort) * size);
	GLushort *normalIndices = ft_memalloc(sizeof(GLushort) * size);

	t_vec4 *temp_positions = ft_memalloc(sizeof(t_vec4) * size);
	t_vec3 *temp_normals = ft_memalloc(sizeof(t_vec3) * size);
	t_vec2 *temp_tx = ft_memalloc(sizeof(t_vec2) * size);

	int vertex_count = 0;
	int texture_count = 0;
	int normal_count = 0;
	int faces_count = 0;
	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp(line, "v ", 2)))
		{
			cutted = ft_strsub(line, 2, ft_strlen(line));
			sub = ft_strsplit(cutted, ' ');

			temp_positions[vertex_count++] =
				vec4_init(atof(sub[0]), atof(sub[1]),atof(sub[2]),1.0f);
			free_strsplit(sub);
			free(cutted);
		}
		else if (!(ft_strncmp(line, "vt ", 3)))
		{
			cutted = ft_strsub(line, 3, ft_strlen(line));
			sub = ft_strsplit(cutted, ' ');
			
			temp_tx[texture_count++] = vec2_init(atof(sub[0]), atof(sub[1]));
			free_strsplit(sub);
			free(cutted);
		}
		else if (!(ft_strncmp(line, "vn ", 3)))
		{
			cutted = ft_strsub(line, 3, ft_strlen(line));
			sub = ft_strsplit(cutted, ' ');

			temp_normals[normal_count++] =
				vec3_init(atof(sub[0]), atof(sub[1]), atof(sub[2]));
			free_strsplit(sub);
			free(cutted);
		}
		else if (!(ft_strncmp(line, "f ", 2)))
		{
			cutted = ft_strsub(line, 2, ft_strlen(line));
			char *trimmed = ft_strtrim(cutted);
			sub = ft_strsplit(trimmed, ' ');
			int i = 0;
			while (++i < get_size(sub) - 1)
			{
				parse(vertexIndices, uvIndices, normalIndices, sub[0], faces_count++);
				parse(vertexIndices, uvIndices, normalIndices, sub[i], faces_count++);
				parse(vertexIndices, uvIndices, normalIndices, sub[i + 1], faces_count++);
				// ft_printf("\n");
			}
			free(cutted);
			free_strsplit(sub);
			free(trimmed);
		}
		free(line);
	}

	for (int v = 0; v < size; v += 3)
	{
		for (unsigned int i = 0; i < 3; i += 1)
		{
			t_vec4 vertex = temp_positions[vertexIndices[v + i] - 1];
			t_vec3 normal = vec3_init(0.0f,0.0f,0.0f);
			t_vec2 uv = vec2_init(0.0f,0.0f);

			if (&temp_normals[0] == NULL)
			{
				normal.x = (temp_positions[vertexIndices[v + i] - 1].x + 1.2)/2.4;
				normal.y = (temp_positions[vertexIndices[v + i] - 1].y + 1.2)/2.4;
				normal.z = (temp_positions[vertexIndices[v + i] - 1].z + 1.2)/2.4;
			}
			else
				normal = temp_normals[normalIndices[v + i] - 1];

			if (&temp_tx[0] != NULL)
				uv = temp_tx[uvIndices[v + i] - 1];
			
			t_vertex ver = {vertex, normal, uv};
			vertices[v + i] = ver;
		}
	}
	update_time(timer);
	printf("%s done in %.2f seconds\n", filename, timer->delta_time);
	free(temp_positions);
	free(temp_normals);
	free(temp_tx);
	free(vertexIndices);
	free(normalIndices);
	free(uvIndices);
}

unsigned int bind_cubemap(char **cubemap_faces)
{
	unsigned int	texture_id;
	int				m_w;
	int				m_h;
	int				m_bpp;
	unsigned char	*data;

	glGenTextures(1, &texture_id);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
	stbi_set_flip_vertically_on_load(0);
	for (GLuint i = 0; i < 6; i++)
	{
		data = stbi_load(cubemap_faces[i], &m_w, &m_h, &m_bpp, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		free(data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return (texture_id);
}

unsigned int bind_texture(char *path)
{
	unsigned int	texture_id;
	int				m_w;
	int				m_h;
	int				m_bpp;
	unsigned char	*data;

	stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &texture_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	data = stbi_load(path, &m_w, &m_h, &m_bpp, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(data);
	return (texture_id);
}

t_binded set_up_object(t_vertex *vertices, int size)
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int program;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(t_vertex),
			&vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
			sizeof(t_vertex), (void*)get_offset(t_vertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
			sizeof(t_vertex), (void*)get_offset(t_vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
			sizeof(t_vertex), (void*)get_offset(t_vertex, texCoords));
	program = read_shaders(
		"res/shaders/vertex_shader.glsl",
		"res/shaders/fragment_shader.glsl");
	return (t_binded){vao, program};
}

t_binded set_up_skybox(t_vertex *vertices, int size)
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int program;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(t_vertex),
			&vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
			sizeof(t_vertex), (void*)get_offset(t_vertex, position));
	program = read_shaders(
		"res/shaders/skybox.vt.glsl",
		"res/shaders/skybox.fg.glsl");
	return (t_binded){vao, program};
}

void print_vec3(t_vec3 vec)
{
	printf("%.0f %.0f %.0f\n", vec.x, vec.y, vec.z);
}

void print_mat4(t_mat4 mat)
{
	printf("%f %f %f %f\n", mat.m11, mat.m12, mat.m13, mat.m14);
	printf("%f %f %f %f\n", mat.m21, mat.m22, mat.m23, mat.m24);
	printf("%f %f %f %f\n", mat.m31, mat.m32, mat.m33, mat.m34);
	printf("%f %f %f %f\n\n", mat.m41, mat.m42, mat.m43, mat.m44);
}

int main(int argc, char **argv)
{
	t_scop		scop;
	SDL_Window	*window;

	window = init_window();
	if (!window)
		put_error("Failed to init window.");
	init_glew(window);
	init_timer(&scop.timer);
	init_keys(scop.key_states);
	scop.camera.position = vec3_init(0.0f, -4.0f, 15.0f);
	scop.camera.direction = vec3_init(0.0f, 0.0f, -1.0f);
	scop.camera.right = vec3_init(-1.0f, 0.0f, 0.0f);
	scop.camera.up = vec3_init(0.0f, -1.0f, 0.0f);
	scop.light.position = vec3_init(0.0f, -10.0f, 0.0f);

	int obj_size = get_size_of_obj(argv[1]);
	if (!obj_size)
		put_error("Invalid obj file.");
	ft_printf("faces_count: %d\n", obj_size);
	t_vertex *vertices = ft_memalloc(sizeof(t_vertex) * obj_size);
	load_obj(&scop.timer, argv[1], vertices, obj_size);
	t_binded bindedObj = set_up_object(vertices, obj_size);

	int skybox_size = get_size_of_obj("res/models/cube/newCube.obj");
	if (!skybox_size)
		put_error("Invalid res/models/cube/newCube.obj skybox file.");
	ft_printf("faces_count: %d\n", skybox_size);
	t_vertex *skybox_vertices = ft_memalloc(sizeof(t_vertex) * skybox_size);
	load_obj(&scop.timer, "res/models/cube/newCube.obj", skybox_vertices, skybox_size);
	t_binded cubemapObj = set_up_skybox(skybox_vertices, skybox_size);

	scop.model = mat4_translate(mat4_identity(), vec3_init(0.0f, 0.0f, 0.0f));
	t_mat4 rotate = mat4_rotate(scop.model, vec3_init(0.0f, 0.0f, 1.0f), TORAD(180.0f)); 
	scop.model = mat4_mul_mat4(scop.model, rotate);

	char *texture_path = "res/models/dragon/dragon.png";
	// const char *path = "res/models/dragon/meta.png";
	// const char *path = "res/models/dragon/tea.png";
	
	char *textures_faces[] = {
		"res/models/Yokohama/posx.jpg",
		"res/models/Yokohama/negx.jpg",
		"res/models/Yokohama/posy.jpg",
		"res/models/Yokohama/negy.jpg",
		"res/models/Yokohama/posz.jpg",
		"res/models/Yokohama/negz.jpg",
	};
	// std::vector<std::string> textures_faces(vinit, std::end(vinit));

	unsigned int objectTextureID = bind_texture(texture_path);
	unsigned int skyboxTextureID = bind_cubemap(textures_faces);

	set_int1(cubemapObj.program, "cubemap", 0);
	set_int1(bindedObj.program, "textureSampler", 0);
	set_int1(bindedObj.program, "enviroMap", 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// glDepthRange(1.0, 1.0);

	while (programIsRunning)
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update_time(&scop.timer);
		handle_events(&scop);

		//как сделать, чтобы скайбокс не перерисовывал обьект

		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(cubemapObj.vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
		draw_skybox(&scop, skybox_size, cubemapObj.program);
		glBindVertexArray(0);
		
		glEnable(GL_DEPTH_TEST);
		glBindVertexArray(bindedObj.vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, objectTextureID);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
		draw_object(&scop, obj_size, bindedObj.program);
		SDL_GL_SwapWindow(window);
	}
	
	system("leaks scop");
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}


void draw_skybox(t_scop *s, unsigned int size, unsigned int program)
{
	t_mat4 look_at = mat4_look_at(s->camera.position, vec3_add(s->camera.position, s->camera.direction), s->camera.up);
	t_mat4 view = mat4_crop_mat3(look_at);
	t_mat4 projection = mat4_projection(TORAD(45.0f), 1.0f * screen_width / screen_height, 0.1f, 100.0f);

	glDepthFunc(GL_LEQUAL);
	set_mat4(program, "projection", projection);
	set_mat4(program, "view", view);
	glDrawArrays(GL_TRIANGLES, 0, size);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}


void draw_object(t_scop *s, unsigned int size, unsigned int program)
{
	t_mat4 view = mat4_look_at(s->camera.position, vec3_add(s->camera.position, s->camera.direction), s->camera.up);
	t_mat4 projection = mat4_projection(TORAD(45.0f), 1.0f * screen_width / screen_height, 0.1f, 1000.0f);

	if (!space_pressed)
	{
		t_mat4 rotate = mat4_rotate(s->model, vec3_init(0.0f, 1.0f, 0.0f), s->timer.delta_time * TORAD(55.0f)); 
		s->model = mat4_mul_mat4(s->model, rotate);
	}

	set_mat4(program, "projection", projection);
	set_mat4(program, "view", view);
	set_mat4(program, "model", s->model);
	set_vec3(program, "lightPos", s->light.position);
	set_int1(program, "mode", mode);

	if (primitive_mode)
	{
		// system("leaks scop");
		glDrawArrays(GL_TRIANGLES, 0, size);
		// system("leaks scop");
		glBindVertexArray(0);
		// exit(1);
	}
	else
	{
		glDrawArrays(GL_LINES, 0, size);
		glBindVertexArray(0);
	}
}