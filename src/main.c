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
			if (e.motion.state & SDL_BUTTON_LMASK)
			{
				if (e.motion.xrel > 0)
					yaw += 1.f;
				else if (e.motion.xrel < 0)
					yaw -= 1.f;
				if (e.motion.yrel > 0)
					pitch += 1.f;
				else if (e.motion.yrel < 0)
					pitch -= 1.f;
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

	if (s->key_states[SDL_SCANCODE_LEFT])
		yaw += 1.f;
	if (s->key_states[SDL_SCANCODE_RIGHT])
		yaw -= 1.f;
	if (s->key_states[SDL_SCANCODE_UP])
		pitch += 1.f;
	if (s->key_states[SDL_SCANCODE_DOWN])
		pitch -= 1.f;

	t_vec3 front;
	front.x = -cos(TORAD(pitch)) * sin(TORAD(-yaw));
	front.y = sin(TORAD(-pitch));
	front.z = -cos(TORAD(pitch)) * cos(TORAD(-yaw));
	s->camera.direction = vec3_normalize(front);
	s->camera.right = vec3_normalize(vec3_cross(s->camera.direction, vec3_init(0.0f, -1.0f, 0.0f)));
	s->camera.up = vec3_normalize(vec3_cross(s->camera.right, s->camera.direction));

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
