/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_locations.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:19:34 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/05 15:19:35 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void set_vec3(unsigned int program, const char *name, t_vec3 vector)
{
	int location = glGetUniformLocation(program, name);
	if (location == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", name);
		exit(0);
	}
	glUniform3fv(location, 1, &vector.x);
}

void set_mat4(unsigned int program, const char *name, t_mat4 matrix)
{
	glUseProgram(program);
	int location = glGetUniformLocation(program, name);
	if (location == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", name);
		exit(0);
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.v[0]);
}

void set_int1(unsigned int program, const char *name, int value)
{
	glUseProgram(program);
	int location = glGetUniformLocation(program, name);
	if (location == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", name);
		exit(0);
	}
	glUniform1i(location, value);
}
