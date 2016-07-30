//
// Created by robertfa on 19.03.16.
//

#include <glm/gtc/type_ptr.hpp>
#include "Triangles.hpp"

void Triangles::subSetup()
{


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(_vertices.data()), _vertices.data(),
				 GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof(_indices.data()),
				 _indices.data(), GL_STATIC_DRAW);
	setVertexAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Triangles::setVertexAttributes() const
{
	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
						  (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

void Triangles::Draw(GLint modelLoc)
{
    glBindVertexArray(VAO);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(_modelMatrix));
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indices.size()),
                       GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

