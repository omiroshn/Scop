/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:20:59 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/05 15:21:00 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
#define SCOP_H

#include <GL/glew.h>
#include <SDL2/SDL.h>

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
#include <iostream>

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

SDL_Window*		InitWindow();
void			InitGlew(SDL_Window * window);

char		**ft_strsplit(char const *s, char c);
int			ft_array_length(char const *s, char c);
char		*ft_strtrim(char const *s);
void		free_strsplit(char **str);
int   read_shaders(const char *vertex_path, const char *fragment_path);

struct Binded
{
	unsigned int vao;
	unsigned int program;
};

void draw_object(unsigned int size, unsigned int program);
void draw_skybox(unsigned int size, unsigned int program);

void setMat4(unsigned int program, const char *name, glm::mat4 matrix);
void setVec3(unsigned int program, const char *name, glm::vec3 vector);
void setInt1(unsigned int program, const char *name, int value);

#endif