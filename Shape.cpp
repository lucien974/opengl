#include "Shape.h"

namespace Core
{
	Shape::Shape(Shader shader)
	: m_texture(nullptr), m_model(1.0), m_vertexSent(false), m_shader(shader),
	m_vaoID(0), m_vboID(0), m_sizeofVertices(0), m_sizeofCoords(0)
	{
	}


	Shape::~Shape()
	{
		// Destruction d'un éventuel ancien VBO
		if(glIsBuffer(m_vboID) == GL_TRUE) {
	        glDeleteBuffers(1, &m_vboID);
	    }

	    // Destruction d'un éventuel ancien VAO
	    if(glIsVertexArray(m_vaoID) == GL_TRUE) {
	        glDeleteVertexArrays(1, &m_vaoID);
	    }
	}


	void Shape::draw(glm::mat4 &projection, glm::mat4 &view)
	{
		assert(m_vboID != 0);
		assert(m_vaoID != 0);

		// Activation du shader
		glUseProgram(m_shader.getProgramID());

			// Verrouillage du VAO
        	glBindVertexArray(m_vaoID);

        		// On envoie les matrices au shader
        		m_shader.sendMat4("modelviewProjection", projection * view * m_model);

			    #ifndef NDEBUG
			    	assert(m_texture != nullptr);
			    #endif

			    sf::Texture::bind(m_texture);

			    #ifndef NDEBUG
			    	// On vérifie que le nombre de points est multiple de 3 (= triangles entiers)
			    	assert(m_vertices.size() % 3 == 0);
			    #endif

        		glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_vertices.size() / 3));

        		sf::Texture::bind(NULL);

        	// Déverrouillage du VAO
        	glBindVertexArray(0);

		// Désactivation du shader
   		glUseProgram(0);
	}


	void Shape::translate(float x, float y, float z)
	{
		m_model = glm::translate(m_model, glm::vec3(x, y, z));
	}


	void Shape::translate(glm::vec3 const &v)
	{
		m_model = glm::translate(m_model, v);
	}


	void Shape::rotate(float rad, float x, float y, float z)
	{
		m_model = glm::rotate(m_model, rad, glm::vec3(x, y, z));
	}


	void Shape::rotate(float rad, glm::vec3 const &v)
	{
		m_model = glm::rotate(m_model, rad, v);
	}


	void Shape::setPosition(float x, float y, float z)
	{
		setPosition(glm::vec3(x, y, z));
	}


	void Shape::setPosition(glm::vec3 const &v)
	{
		m_model = glm::mat4(1.0);
		translate(v);
	}


	void Shape::sendVertex()
	{
		if(m_vertexSent) {
			throw std::runtime_error("Vertex already sent");
		}
		genVBO();
		genVAO();
		m_vertexSent = true;
	}


	/*
	TODO: Prendre en charge la frequence de changement:
	 - GL_STATIC_DRAW : pour les données très peu mises à jour
	 - GL_DYNAMIC_DRAW : pour les données mises à jour fréquemment (plusieurs fois par seconde mais pas à chaque frame)
	 - GL_STREAM_DRAW : pour les données mises à jour tout le temps
	*/
	void Shape::genVBO()
	{
		// Destruction d'un éventuel ancien VBO
	    if(glIsBuffer(m_vboID) == GL_TRUE) {
	        glDeleteBuffers(1, &m_vboID);
	    }

    	m_sizeofVertices = m_vertices.size() * sizeof(float);
    	m_sizeofCoords = m_coords.size() * sizeof(float);

    	if(m_sizeofVertices == 0) {
			throw std::runtime_error("No vertices sent");
    	}

    	if(m_sizeofCoords == 0) {
			throw std::runtime_error("No coords sent");
    	}


    	// Creation du Vertex Buffer Object
    	glGenBuffers(1, &m_vboID);

    	// Verrouillage du VBO
    	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	    	// Allocation de la mémoire de la carte graphique
	        glBufferData(GL_ARRAY_BUFFER, m_sizeofVertices + m_sizeofCoords, 0, GL_STATIC_DRAW);

		        //Transfert
		        glBufferSubData(GL_ARRAY_BUFFER, 0, m_sizeofVertices, &m_vertices[0]);
		        glBufferSubData(GL_ARRAY_BUFFER, m_sizeofVertices, m_sizeofCoords, &m_coords[0]);

		// Déverrouillage du VBO
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	void Shape::genVAO()
	{
		// Destruction d'un éventuel ancien VAO
	    if(glIsVertexArray(m_vaoID) == GL_TRUE)
        {
	        glDeleteVertexArrays(1, &m_vaoID);
	    }

		// Creation du Vertex Array Object
	    glGenVertexArrays(1, &m_vaoID);

	    // Verrouillage du VAO
    	glBindVertexArray(m_vaoID);

		    // Verrouillage du VBO
			glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

			    // Accès aux vertices dans la mémoire vidéo
			    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			    glEnableVertexAttribArray(0);

			    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_sizeofVertices));
    			glEnableVertexAttribArray(2);

			// Déverrouillage du VBO
			glBindBuffer(GL_ARRAY_BUFFER, 0);

	    // Déverrouillage du VAO
    	glBindVertexArray(0);
	}

}
