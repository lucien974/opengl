#include "Object.h"

Object3D::Object3D(std::string obj_filename, Core::Shader &shader)
: m_shader(shader)
{
    initialize(obj_filename);
}

void Object3D::initialize(std::string filename)
{
    /*
    m_use_nor = m_use_tex = false;
    std::deque<glm::vec3> v, n;
    std::deque<glm::vec2> t;
    m_file.open(m_filename + ".obj" , std::ios::in);
    std::string obj_id;
    if(m_file)
    {
        while(m_file.eof() != true)
        {
            m_file >> obj_id;
            switch(obj_id[0])
            {
                case 'v':
                    switch(obj_id[1])
                    {
                        case 'n':
                            readNormal(n);
                            break;
                        case 't':
                            readTexCrd(t);
                            break;
                        default:
                            readVertex(v);
                            break;
                    }
                    break;
                case 'f':
                    readFace(v, t, n);
                    break;
                case 'c':
                    readCenter();
                default:
                    std::cout << "default : " << obj_id[1] << std::endl;
                    break;
            }
        }
        return true;
    }
    return false;
    //*/
}
