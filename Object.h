#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Model.h"

class Object3D
{
    public:
        Object3D(std::string obj_filename, Core::Shader &shader);

    private:
        void initialize(std::string filename);
		void readCenter();
		void readVertex(std::deque<glm::vec3> &v);
		void readTexCrd(std::deque<glm::vec2> &t);
		void readNormal(std::deque<glm::vec3> &n);
		void readFace(std::deque<glm::vec3> &v, std::deque<glm::vec2> &t, std::deque<glm::vec3> &n);

        std::map<int, Model> m_models;
        Core::Shader m_shader;
};


#endif // OBJECT_H_INCLUDED
