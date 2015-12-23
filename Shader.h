#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <fstream>

#include "Headers.h"

namespace Core
{
	class Shader
	{
	    public:
		    Shader(Shader const &shaderACopier);
		    Shader(std::string vertexSource, std::string fragmentSource);
		    ~Shader();
		    Shader& operator=(Shader const &shaderACopier);
		    GLuint getProgramID() const;
		    void sendMat4(std::string name, glm::mat4 matrix);
		    void setOffset(unsigned int offset);

	    private:
		    bool load();
		    bool compile(GLuint &shader, GLenum type, std::string const &fichierSource);
		    GLuint m_vertexID;
		    GLuint m_fragmentID;
		    GLuint m_programID;
		    std::string m_vertexSource;
		    std::string m_fragmentSource;
	};
}

#endif //SHADER_H
