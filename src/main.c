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

void	prepare_scene(t_scop *scop, char *filename, char *texture_filename)
{
	scop->obj_size = get_size_of_obj(filename);
	if (!scop->obj_size)
		put_error("Invalid obj file.");
	scop->binded_obj = load_obj(&scop->timer, filename, scop->obj_size, 0);
	scop->skybox_size = get_size_of_obj("res/models/cube/newCube.obj");
	if (!scop->skybox_size)
		put_error("Invalid res/models/cube/newCube.obj skybox file.");
	scop->cubemap_obj = load_obj(&scop->timer, "res/models/cube/newCube.obj",
		scop->skybox_size, 1);
	scop->object_texture_id = bind_texture(texture_filename);
	scop->skybox_texture_id = bind_cubemap();
	set_int1(scop->cubemap_obj.program, "cubemap", 0);
	set_int1(scop->binded_obj.program, "textureSampler", 0);
	set_int1(scop->binded_obj.program, "enviroMap", 1);
}

void	main_loop(t_scop scop, SDL_Window *window)
{
	while (scop.program_is_running)
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update_time(&scop.timer);
		handle_events(&scop);
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(scop.cubemap_obj.vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, scop.skybox_texture_id);
		draw_skybox(&scop, scop.skybox_size, scop.cubemap_obj.program);
		glEnable(GL_DEPTH_TEST);
		glBindVertexArray(scop.binded_obj.vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scop.object_texture_id);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, scop.skybox_texture_id);
		draw_object(&scop, scop.obj_size, scop.binded_obj.program);
		SDL_GL_SwapWindow(window);
	}
}

int		main(int argc, char **argv)
{
	t_scop			scop;
	SDL_Window		*window;
	SDL_GLContext	context;

	window = init_window();
	if (!window)
		put_error("Failed to init window.");
	context = init_glew(window);
	init_timer(&scop.timer);
	init_keys(scop.key_states);
	init_scop(&scop);
	prepare_scene(&scop, argv[1], argv[2]);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	main_loop(scop, window);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (argc);
}
