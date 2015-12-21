#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Model.h"

class Object3D
{
    public:
        Object3D(std::string obj_filename, Core::Shader &shader);
    private:
        std::map<int, Model> m_models;
};


#endif // OBJECT_H_INCLUDED
