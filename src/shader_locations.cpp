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
#include "debug.h"

void setVec3(unsigned int program, const char *name, glm::vec3 vector)
{
	GLCall(int location = glGetUniformLocation(program, name));
	if (location == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", name);
		exit(0);
	}
	GLCall(glUniform3fv(location, 1, &vector.x));
}

void setMat4(unsigned int program, const char *name, glm::mat4 matrix)
{
	GLCall(glUseProgram(program));
	GLCall(int location = glGetUniformLocation(program, name));
	if (location == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", name);
		exit(0);
	}
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}
