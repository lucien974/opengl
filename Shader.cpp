#include "Shader.h"

namespace Core
{
    Shader::Shader(Shader const &shaderACopier): m_programID(shaderACopier.getProgramID()), m_vertexSource(shaderACopier.m_vertexSource), m_fragmentSource(shaderACopier.m_fragmentSource)
    {
        // Chargement du nouveau shader
        std::cout << "shader loading..." << std::endl;
        load();
        std::cout << "shader loaded" << std::endl;
    }


    Shader::Shader(std::string vertexSource, std::string fragmentSource)
    : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
    {
        load();
    }


    Shader::~Shader()
    {
        // Destruction du shader
        glDeleteShader(m_vertexID);
        glDeleteShader(m_fragmentID);
        glDeleteProgram(m_programID);
    }


    Shader& Shader::operator=(Shader const &shaderACopier)
    {
        // Copie des fichiers sources
        m_vertexSource = shaderACopier.m_vertexSource;
        m_fragmentSource = shaderACopier.m_fragmentSource;

        // Chargement du nouveau shader
        load();

        // Retour du pointeur this
        return *this;
    }

    void Shader::setOffset(unsigned int offset)
    {
        if (offset != 0)
        {
            glBindAttribLocation(m_programID, offset, "in_Vertex");
            glBindAttribLocation(m_programID, offset+1, "in_Color");
            glBindAttribLocation(m_programID, offset+2, "in_TexCoord0");
        }
    }


    bool Shader::load()
    {
        // Destruction d'un éventuel ancien Shader
        if(glIsShader(m_vertexID) == GL_TRUE)
        {
            ++m_vertexID;
            //glDeleteShader(m_vertexID);
        }

        if(glIsShader(m_fragmentID) == GL_TRUE)
        {
            ++m_fragmentID;
            //glDeleteShader(m_fragmentID);
        }

        if(glIsProgram(m_programID) == GL_TRUE)
        {
            ++m_programID;
            //glDeleteProgram(m_programID);
        }

        if(!compile(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        {
            return false;
        }

        if(!compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        {
            return false;
        }

        // Création du programme
        m_programID = glCreateProgram();

        // Association des shaders
        glAttachShader(m_programID, m_vertexID);
        glAttachShader(m_programID, m_fragmentID);

        // Verrouillage des entrées shader
        glBindAttribLocation(m_programID, 0, "in_Vertex");
        glBindAttribLocation(m_programID, 1, "in_Color");
        glBindAttribLocation(m_programID, 2, "in_TexCoord0");

        // Linkage du programme
        glLinkProgram(m_programID);

        // Vérification du linkage
        GLint erreurLink(0);
        glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);

        // S'il y a eu une erreur
        if(erreurLink != GL_TRUE) {
            // Récupération de la taille de l'erreur
            GLint tailleErreur(0);
            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);

            // Allocation de mémoire
            char *erreur = new char[tailleErreur + 1];

            // Récupération de l'erreur
            glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
            erreur[tailleErreur] = '\0';

            // Affichage de l'erreur
            std::cout << erreur << std::endl;

            // Libération de la mémoire et retour du booléen false
            delete[] erreur;
            glDeleteProgram(m_programID);

            return false;
        }
        return true;
    }


    bool Shader::compile(GLuint &shader, GLenum type, std::string const &fichierSource)
    {
        // Création du shader
        shader = glCreateShader(type);

        // Vérification du shader
        if(shader == 0) {
            std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
            return false;
        }

        // Flux de lecture
        std::ifstream fichier(fichierSource.c_str());

        // Test d'ouverture
        if(!fichier) {
            std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
            glDeleteShader(shader);

            return false;
        }

        // Strings permettant de lire le code source
        std::string ligne;
        std::string codeSource;

        std::cout << "shader read" << std::endl;
        // Lecture
        while(getline(fichier, ligne)) {
            codeSource += ligne + '\n';
        }

        // Fermeture du fichier
        fichier.close();

        // Récupération de la chaine C du code source
        const GLchar* chaineCodeSource = codeSource.c_str();

        // Envoi du code source au shader
        glShaderSource(shader, 1, &chaineCodeSource, 0);

        // Compilation du shader
        glCompileShader(shader);

        // Vérification de la compilation
        GLint erreurCompilation(0);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

        // S'il y a eu une erreur
        if(erreurCompilation != GL_TRUE) {
            // Récupération de la taille de l'erreur
            GLint tailleErreur(0);
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);

            // Allocation de mémoire
            char *erreur = new char[tailleErreur + 1];

            // Récupération de l'erreur
            glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
            erreur[tailleErreur] = '\0';

            // Affichage de l'erreur
            std::cout << erreur << std::endl;

            // Libération de la mémoire et retour du booléen false
            delete[] erreur;
            glDeleteShader(shader);

            return false;
        }
        return true;
    }


    GLuint Shader::getProgramID() const
    {
        return m_programID;
    }


    void Shader::sendMat4(std::string name, glm::mat4 matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(getProgramID(), name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

}
