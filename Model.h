#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <deque>
#include "Shape.h"
#include "Shader.h"
#include "Textureloader.h"

struct Face
{
    glm::vec3 vertex[3];
    glm::vec2 texcoords[3];
    glm::vec3 normal[3];
};

class Model : public Core::Shape
{
	public:
		Model(std::string filename , std::string texture ,  Textureloader* textload, Core::Shader &shader);
		Model(std::deque<float> vertex, std::deque<float> texcrd, std::deque<float> normls, Core::Shader &shader);
		void update(glm::mat4& projection, glm::mat4& view);
	private:
		bool load();
		void initialize();
		void readCenter();
		void readVertex(std::deque<glm::vec3> &v);
		void readTexCrd(std::deque<glm::vec2> &t);
		void readNormal(std::deque<glm::vec3> &n);
		void readFace(std::deque<glm::vec3> &v, std::deque<glm::vec2> &t, std::deque<glm::vec3> &n);

		std::string m_filename;
		Textureloader *m_textload;
		bool m_use_tex, m_use_nor;
		std::fstream m_file;
		glm::vec3 m_center;
		std::deque<Face> m_faces;
};

#endif // MODEL_H_INCLUDED
