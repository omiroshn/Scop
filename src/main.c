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

float yaw   = 0.0f;
float pitch =  0.0f;

float mouseOffsetX = 0.0f;
float mouseOffsetY = 0.0f;
float prevMousePosX = 0.0f;
float prevMousePosY = 0.0f;
float mouseSensitivity = 0.05f;

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
					yaw -= 1.0f;
				else if (e.motion.xrel < 0)
					yaw += 1.0f;
				if (e.motion.yrel > 0)
					pitch -= 1.0f;
				else if (e.motion.yrel < 0)
					pitch += 1.0f;

				t_vec3 front;
				front.x = -cos(TORAD(pitch)) * sin(TORAD(-yaw));
				front.y = sin(TORAD(-pitch));
				front.z = -cos(TORAD(pitch)) * cos(TORAD(-yaw));
				s->camera.direction = vec3_normalize(front);
				s->camera.right = vec3_normalize(vec3_cross(s->camera.direction, vec3_init(0.0f, -1.0f, 0.0f)));
				s->camera.up = vec3_normalize(vec3_cross(s->camera.right, s->camera.direction));
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
	// if (s->key_states[SDL_SCANCODE_I])
	// 	s->light.position += s->camera.direction * cameraSpeed;
	// if (s->key_states[SDL_SCANCODE_K])
	// 	s->light.position -= s->camera.direction * cameraSpeed;
	// if (s->key_states[SDL_SCANCODE_L])
	// 	s->light.position += s->camera.right * cameraSpeed;
	// if (s->key_states[SDL_SCANCODE_J])
	// 	s->light.position -= s->camera.right * cameraSpeed;
	// if (s->key_states[SDL_SCANCODE_U])
	// 	s->light.position += s->camera.up * cameraSpeed;
	// if (s->key_states[SDL_SCANCODE_O])
	// 	s->light.position -= s->camera.up * cameraSpeed;

	if (s->key_states[SDL_SCANCODE_I])
		s->light.position = vec3_add(s->light.position, vec3_mult_scalar(s->camera.direction, cameraSpeed));
	if (s->key_states[SDL_SCANCODE_K])
		s->light.position = vec3_sub(s->light.position, vec3_mult_scalar(s->camera.direction, cameraSpeed));
	if (s->key_states[SDL_SCANCODE_L])
		s->light.position = vec3_add(s->light.position, vec3_mult_scalar(s->camera.right, cameraSpeed));
	if (s->key_states[SDL_SCANCODE_J])
		s->light.position = vec3_sub(s->light.position, vec3_mult_scalar(s->camera.right, cameraSpeed));
	if (s->key_states[SDL_SCANCODE_U])
		s->light.position = vec3_add(s->light.position, vec3_mult_scalar(s->camera.up, cameraSpeed));
	if (s->key_states[SDL_SCANCODE_O])
		s->light.position = vec3_sub(s->light.position, vec3_mult_scalar(s->camera.up, cameraSpeed));

	if (s->key_states[SDL_SCANCODE_LEFT])
		yaw += 1.f;
	if (s->key_states[SDL_SCANCODE_RIGHT])
		yaw -= 1.f;
	if (s->key_states[SDL_SCANCODE_UP])
		pitch += 1.f;
	if (s->key_states[SDL_SCANCODE_DOWN])
		pitch -= 1.f;
}

void prepare_scene(t_scop *scop, char *filename, char *texture_filename)
{
	scop->obj_size = get_size_of_obj(filename);
	if (!scop->obj_size)
		put_error("Invalid obj file.");
	scop->bindedObj = load_obj(&scop->timer, filename, scop->obj_size, 0);
	scop->skybox_size = get_size_of_obj("res/models/cube/newCube.obj");
	if (!scop->skybox_size)
		put_error("Invalid res/models/cube/newCube.obj skybox file.");
	scop->cubemapObj = load_obj(&scop->timer, "res/models/cube/newCube.obj", scop->skybox_size, 1);
	scop->model = mat4_translate(mat4_identity(), vec3_init(0.0f, 0.0f, 0.0f));
	scop->model = mat4_rotate(scop->model, vec3_init(0.0f, 0.0f, 1.0f), TORAD(180.0f));
	scop->objectTextureID = bind_texture(texture_filename);
	scop->skyboxTextureID = bind_cubemap();
	set_int1(scop->cubemapObj.program, "cubemap", 0);
	set_int1(scop->bindedObj.program, "textureSampler", 0);
	set_int1(scop->bindedObj.program, "enviroMap", 1);
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
	prepare_scene(&scop, argv[1], argv[2]);

	//6
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);

	while (scop.program_is_running)
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update_time(&scop.timer);
		handle_events(&scop);

		//как сделать, чтобы скайбокс не перерисовывал обьект

		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(scop.cubemapObj.vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, scop.skyboxTextureID);
		draw_skybox(&scop, scop.skybox_size, scop.cubemapObj.program);
		
		// glEnable(GL_DEPTH_TEST);
		// glBindVertexArray(scop.bindedObj.vao);
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, scop.objectTextureID);
		// glActiveTexture(GL_TEXTURE0 + 1);
		// glBindTexture(GL_TEXTURE_CUBE_MAP, scop.skyboxTextureID);
		// draw_object(&scop, scop.obj_size, scop.bindedObj.program);
		SDL_GL_SwapWindow(window);
	}
	argc++;
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
