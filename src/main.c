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

// bool mRightButtonPressed = false;


// t_vec3 mWorldUp(0.0f, 1.0f, 0.0f);
// t_vec3 mWorldRight(1.0f, 0.0f, 0.0f);
// t_vec3 cameraFront(0.0f, 0.0f, -1.0f);


float yaw   = 0.0f;
float pitch =  0.0f;

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
			s->program_is_running = 0;
		else if (e.type == SDL_KEYDOWN)
		{
			s->key_states[e.key.keysym.scancode] = 1;
			if (e.key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET)
				--s->mode < 1 ? s->mode = 6 : 0;
			if (e.key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET)
				++s->mode > 6 ? s->mode = 1 : 0;
			if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
				s->space_pressed ^= 1;
			if (e.key.keysym.scancode == SDL_SCANCODE_P)
				s->primitive_mode ^= 1;
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

    if (s->key_states[SDL_SCANCODE_LEFT])
		yaw += 1.f;
	if (s->key_states[SDL_SCANCODE_RIGHT])
		yaw -= 1.f;
	if (s->key_states[SDL_SCANCODE_UP])
		pitch += 1.f;
	if (s->key_states[SDL_SCANCODE_DOWN])
		pitch -= 1.f;

		// -cos(pitch * PI / 180.0) * sin(yaw * PI / 180.0)
		// sin(pitch * PI / 180.0)
		// -cos(pitch * PI / 180.0) * cos(yaw * PI / 180.0);



		t_vec3 front;
		// std::cout << "yaw " << cos(ceil(degreesToRadians(yaw))) << " " << ceil(degreesToRadians(yaw)) << " " << degreesToRadians(yaw) << " " << yaw << std::endl;
	    front.x = -cos(TORAD(pitch)) * sin(TORAD(-yaw));
	    front.y = sin(TORAD(-pitch));
	    front.z = -cos(TORAD(pitch)) * cos(TORAD(-yaw));

	    // std::cout << "front " << front.x << " " << front.y << " " << front.z << std::endl;
		s->camera.direction = vec3_normalize(front);
	    s->camera.right = vec3_normalize(vec3_cross(s->camera.direction, vec3_init(0.0f, -1.0f, 0.0f)));
	    s->camera.up = vec3_normalize(vec3_cross(s->camera.right, s->camera.direction));
		// std::cout << "cameraDir " << cameraDir.x << " " << cameraDir.y << " " << cameraDir.z << std::endl;
		// std::cout << "cameraRight " << cameraRight.x << " " << cameraRight.y << " " << cameraRight.z << std::endl;
		// std::cout << "cameraUp " << cameraUp.x << " " << cameraUp.y << " " << cameraUp.z << std::endl;

}


int get_size(char **sub)
{
	int i;

	i = 1;
	while (*++sub)
		i++;
	return (i);
}

// создать 3 массива под величины
// записать их в 1
// затосовать
// записать в 1 и вернуть

// или записывать сразу в 1


int	get_faces(char *line)
{
	char			*cutted;
	char			**sub;
	char			*trimmed;
	int				i;
	int				faces_count;

	faces_count = 0;
	cutted = ft_strsub(line, 2, ft_strlen(line));
	trimmed = ft_strtrim(cutted);
	sub = ft_strsplit(trimmed, ' ');
	i = 1;
	while (i++ < get_size(sub) - 1)
		faces_count += 3;
	free(cutted);
	free_strsplit(sub);
	free(trimmed);
	return (faces_count);
}

int get_size_of_obj(char *filename)
{
	int				fd;
	char			*line;
	int				faces;

	ft_printf("Reading: %s\n", filename);
	if ((fd = open(filename, O_RDONLY)) < 0 || read(fd, NULL, 0) < 0)
		put_error("Failed to open file.");
	faces = 0;
	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp(line, "f ", 2)))
			faces += get_faces(line);
		free(line);
	}
	close(fd);
	return (faces);
}

t_vec4	cut_vertex_string(char *line)
{
	char	*cutted;
	char	**sub;
	t_vec4	vec;

	cutted = ft_strsub(line, 2, ft_strlen(line));
	sub = ft_strsplit(cutted, ' ');
	vec = vec4_init(atof(sub[0]), atof(sub[1]), atof(sub[2]), 1.0f);
	free_strsplit(sub);
	free(cutted);
	return (vec);
}

t_vec2	cut_texture_string(char *line)
{
	char	*cutted;
	char	**sub;
	t_vec2	vec;

	cutted = ft_strsub(line, 3, ft_strlen(line));
	sub = ft_strsplit(cutted, ' ');
	vec = vec2_init(atof(sub[0]), atof(sub[1]));
	free_strsplit(sub);
	free(cutted);
	return (vec);
}

t_vec3	cut_normal_string(char *line)
{
	char	*cutted;
	char	**sub;
	t_vec3	vec;

	cutted = ft_strsub(line, 3, ft_strlen(line));
	sub = ft_strsplit(cutted, ' ');
	vec = vec3_init(atof(sub[0]), atof(sub[1]), atof(sub[2]));
	free_strsplit(sub);
	free(cutted);
	return (vec);
}

void	cut_face_string(GLushort *vertex_indices, GLushort *uv_indices,
			GLushort *normal_indices, char *line, int *faces_count)
{
	char	*cutted;
	char	*trimmed;
	char	**sub;
	int		i;

	cutted = ft_strsub(line, 2, ft_strlen(line));
	trimmed = ft_strtrim(cutted);
	sub = ft_strsplit(trimmed, ' ');
	i = 0;
	while (++i < get_size(sub) - 1)
	{
		parse(vertex_indices, uv_indices, normal_indices, sub[0], (*faces_count)++);
		parse(vertex_indices, uv_indices, normal_indices, sub[i], (*faces_count)++);
		parse(vertex_indices, uv_indices, normal_indices, sub[i + 1], (*faces_count)++);
	}
	free(cutted);
	free_strsplit(sub);
	free(trimmed);
}

void	init_temp_struct(t_tmp_vertex *v, int size)
{
	v->vertex = ft_memalloc(sizeof(t_vec4) * size);
	v->uv = ft_memalloc(sizeof(t_vec2) * size);
	v->normal = ft_memalloc(sizeof(t_vec3) * size);
	v->vertex_indices = ft_memalloc(sizeof(GLushort) * size);
	v->uv_indices = ft_memalloc(sizeof(GLushort) * size);
	v->normal_indices = ft_memalloc(sizeof(GLushort) * size);
}

void	free_tmp_struct(t_tmp_vertex *v)
{
	free(v->vertex);
	free(v->uv);
	free(v->normal);
	free(v->vertex_indices);
	free(v->uv_indices);
	free(v->normal_indices);
}

void	fill_vertex_array(t_vertex *vertices, t_tmp_vertex v, int size)
{
	int			j;
	int			i;
	t_vertex	vertex;

	j = 0;
	while (j < size && (i = -1))
	{
		while (++i < 3)
		{
			vertex.position = v.vertex[v.vertex_indices[j + i] - 1];
			vertex.normal = vec3_init(0.0f, 0.0f, 0.0f);
			vertex.texCoords = vec2_init(0.0f, 0.0f);
			vertex.normal = v.normal[v.normal_indices[j + i] - 1];
			if (&v.normal[0] == NULL)
			{
				vertex.normal.x = (v.vertex[v.vertex_indices[j + i] - 1].x + 1.2) / 2.4;
				vertex.normal.y = (v.vertex[v.vertex_indices[j + i] - 1].y + 1.2) / 2.4;
				vertex.normal.z = (v.vertex[v.vertex_indices[j + i] - 1].z + 1.2) / 2.4;
			}	
			if (&v.uv[0] != NULL)
				vertex.texCoords = v.uv[v.uv_indices[j + i] - 1];
			vertices[j + i] = vertex;
		}
		j += 3;
	}
}

void	load_obj(t_timer *timer, const char *filename, t_vertex *vertices, int size)
{
	int				fd;
	char 			*line;
	t_tmp_vertex	v;

	fd = open(filename, O_RDONLY);
	init_temp_struct(&v, size);

	int vertex_count = 0;
	int texture_count = 0;
	int normal_count = 0;
	int faces_count = 0;
	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp(line, "v ", 2)))
			v.vertex[vertex_count++] = cut_vertex_string(line);
		else if (!(ft_strncmp(line, "vt ", 3)))
			v.uv[texture_count++] = cut_texture_string(line);
		else if (!(ft_strncmp(line, "vn ", 3)))
			v.normal[normal_count++] = cut_normal_string(line);
		else if (!(ft_strncmp(line, "f ", 2)))
			cut_face_string(v.vertex_indices, v.uv_indices, v.normal_indices, line, &faces_count);
		free(line);
	}
	fill_vertex_array(vertices, v, size);
	update_time(timer);
	ft_printf("%s done in %.2f seconds\n", filename, timer->delta_time);
	free_tmp_struct(&v);
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

void prepare_scene(t_scop scop)
{
	

	
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
	init_scop(&scop);
	prepare_scene(scop);

	//1 load obj
	int obj_size = get_size_of_obj(argv[1]);
	if (!obj_size)
		put_error("Invalid obj file.");
	ft_printf("faces_count: %d\n", obj_size);
	t_vertex *vertices = ft_memalloc(sizeof(t_vertex) * obj_size);
	load_obj(&scop.timer, argv[1], vertices, obj_size);
	t_binded bindedObj = set_up_object(vertices, obj_size);

	//2 load skybox
	int skybox_size = get_size_of_obj("res/models/cube/newCube.obj");
	if (!skybox_size)
		put_error("Invalid res/models/cube/newCube.obj skybox file.");
	ft_printf("faces_count: %d\n", skybox_size);
	t_vertex *skybox_vertices = ft_memalloc(sizeof(t_vertex) * skybox_size);
	load_obj(&scop.timer, "res/models/cube/newCube.obj", skybox_vertices, skybox_size);
	t_binded cubemapObj = set_up_skybox(skybox_vertices, skybox_size);

	//3 rotate model upsidesdown
	scop.model = mat4_translate(mat4_identity(), vec3_init(0.0f, 0.0f, 0.0f));
	scop.model = mat4_rotate(scop.model, vec3_init(0.0f, 0.0f, 1.0f), TORAD(180.0f)); 

	//4 load textures from argv

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
	unsigned int objectTextureID = bind_texture(texture_path);
	unsigned int skyboxTextureID = bind_cubemap(textures_faces);

	//5
	set_int1(cubemapObj.program, "cubemap", 0);
	set_int1(bindedObj.program, "textureSampler", 0);
	set_int1(bindedObj.program, "enviroMap", 1);

	//6
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// glDepthRange(1.0, 1.0);

	while (scop.program_is_running)
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
