#include "Model.h"

Model::Model(std::string filename , std::string texture ,  Textureloader* textload, Core::Shader &shader) : Shape(shader)
{
    m_filename = filename;
    initialize();
    m_textload = textload;
    m_texture = &m_textload->getTexture(texture);
}

Model::Model(std::deque<float> vertex, std::deque<float> texcrd, std::deque<float> normls, Core::Shader &shader) : Shape(shader)
{

}

bool Model::load()
{
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
}

void Model::readVertex(std::deque<glm::vec3> &v)
{
    glm::vec3 vertex;
    m_file >> vertex.x >> vertex.y >> vertex.z;
    v.push_back(vertex);
}

void Model::readTexCrd(std::deque<glm::vec2> &t)
{
    m_use_tex = true;
    glm::vec2 texcoord;
    m_file >> texcoord.x >> texcoord.y;
    t.push_back(texcoord);
}

void Model::readNormal(std::deque<glm::vec3> &n)
{
    m_use_nor = true;
    glm::vec3 normal;
    m_file >> normal.x >> normal.y >> normal.z;
    n.push_back(normal);
}

void Model::readCenter()
{
    m_file >> m_center.x >> m_center.y >> m_center.z;
}

void Model::readFace(std::deque<glm::vec3> &v, std::deque<glm::vec2> &t, std::deque<glm::vec3> &n)
{
    Face temp;
    int inter[9];
    if(m_use_tex)
    {
        if(m_use_nor)
        {
            for(int i(0) ; i < 9 ; i++)
                m_file >> inter[i];
            temp.vertex[0] = v[inter[0]-1];
            temp.texcoords[0] = t[inter[1]-1];
            temp.normal[0] = n[inter[2]-1];
            temp.vertex[1] = v[inter[3]-1];
            temp.texcoords[1] = t[inter[4]-1];
            temp.normal[1] = n[inter[5]-1];
            temp.vertex[2] = v[inter[6]-1];
            temp.texcoords[2] = t[inter[7]-1];
            temp.normal[2] = n[inter[8]-1];
        }
        else
        {
            for(int i(0) ; i < 6 ; i++)
            {
                m_file >> inter[i];
            }
            temp.vertex[0] = v[inter[0]-1];
            temp.texcoords[0] = t[inter[1]-1];
            temp.vertex[1] = v[inter[2]-1];
            temp.texcoords[1] = t[inter[3]-1];
            temp.vertex[2] = v[inter[4]-1];
            temp.texcoords[2] = t[inter[5]-1];
        }
    }
    else
    {
        if(m_use_nor)
        {
            for(int i(0) ; i < 6 ; i++)
                m_file >> inter[i];
            temp.vertex[0] = v[inter[0]-1];
            temp.vertex[1] = v[inter[1]-1];
            temp.vertex[2] = v[inter[2]-1];
            temp.normal[0] = n[inter[6]-1];
            temp.normal[1] = n[inter[7]-1];
            temp.normal[2] = n[inter[8]-1];
        }
        else
        {
            for(int i(0) ; i < 3 ; i++)
                m_file >> inter[i];
            temp.vertex[0] = v[inter[0]-1];
            temp.vertex[1] = v[inter[1]-1];
            temp.vertex[2] = v[inter[2]-1];
        }
    }
    m_faces.push_back(temp);
}

void Model::initialize()
{
    if(!load())
        throw std::runtime_error("OBJ file empty");
        /**/
    //std::cout << "number of faces : " << m_faces.size() << std::endl;
    for(unsigned int i(0) ; i < m_faces.size() ; ++i)
    {
        for(int z(0); z < 3; ++z)
        {
            m_vertices.push_back(m_faces[i].vertex[z].x);
            m_vertices.push_back(m_faces[i].vertex[z].y);
            m_vertices.push_back(m_faces[i].vertex[z].z);
        }
    }
    if(m_use_tex)
    {
        for(unsigned int i(0) ; i < m_faces.size() ; ++i)
        {
            for(int z(0); z < 3; ++z)
            {
                m_coords.push_back(m_faces[i].texcoords[z].x);
                m_coords.push_back(m_faces[i].texcoords[z].y);
            }
        }
    }
    //*/
    /*
    if(m_use_nor)
    {
        for(unsigned int i(0) ; i < m_faces.size() ; ++i)
        {
            for(int z(0); z < 3; ++z)
            {
                m_vertex.push_back(m_faces[i].normal[z].x);
                m_vertex.push_back(m_faces[i].normal[z].y);
                m_vertex.push_back(m_faces[i].normal[z].z);
            }
        }
    }
    //*/
    std::cout << "sending" << std::endl;
    sendVertex();
    std::cout << "vertex sent" << std::endl;
}

void Model::update(glm::mat4& projection, glm::mat4& view)
{
    draw(projection, view);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
        rotate(0.1, glm::vec3(1.0, 0.0, 0.0));
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
        rotate(0.1, glm::vec3(-1.0, 0.0, 0.0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
        rotate(0.1, glm::vec3(0.0, 0.0, 1.0));
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
        rotate(0.1, glm::vec3(0.0, 0.0, -1.0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
        rotate(0.1, glm::vec3(0.0, 1.0, 0.0));
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
        rotate(0.1, glm::vec3(0.0, -1.0, 0.0));
}
