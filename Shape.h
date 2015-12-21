#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <exception>
#include "Headers.h"
#include "Shader.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

namespace Core
{
	class Shape
	{
		public:
			Shape(Shader shader);
			~Shape();
			void draw(glm::mat4 &projection, glm::mat4 &view);
			void translate(float x, float y, float z);
			void translate(glm::vec3 const &v);
			void rotate(float rad, float x, float y, float z);
			void rotate(float rad, glm::vec3 const &v);
			void setPosition(float x, float y, float z);
			void setPosition(glm::vec3 const &v);

		protected:
			void sendVertex();
			std::vector<GLfloat> m_vertices;
			std::vector<GLfloat> m_coords;
			sf::Texture *m_texture;
			glm::mat4 m_model;

		private:
			void genVBO();
			void genVAO();
			bool m_vertexSent;
			Shader m_shader;
			GLuint m_vaoID;
			GLuint m_vboID;
			unsigned long int m_sizeofVertices;
			unsigned long int m_sizeofCoords;
	};
}

#endif //SHAPE_H
