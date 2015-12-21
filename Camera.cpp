#include "Camera.h"

namespace Core
{
	Camera::Camera()
	: m_phi(0.0f), m_theta(0.0f), m_sensibility(0), m_speed(0), m_orientation(), m_verticalAxis(0, 0, 1), m_sideshift(), m_position(), m_target(), m_view(glm::mat4(1.0)), m_mouse()
	{
	}


	Camera::Camera(sf::RenderWindow* screen, glm::vec3 position, glm::vec3 target, glm::vec3 verticalAxis, float sensibility, float speed)
	: m_sensibility(sensibility), m_speed(speed), m_orientation(), m_verticalAxis(verticalAxis), m_sideshift(), m_position(position), m_target(target), m_view(glm::mat4(1.0)), m_screen(screen)
	{
	    glm::vec3 direction;
	    direction = m_target - m_position;
	    if(m_verticalAxis.x == 1.0f)
        { // Si l'axe vertical est l'axe X
		    direction = glm::normalize(direction);
            m_phi = std::asin(direction.x);
            m_theta = std::acos(direction.y/std::cos(m_phi));
            m_phi *= 180.0/PI;
            m_theta *= 180.0/PI;
		}
		else if(m_verticalAxis.y == 1.0f)
		{ // Si c'est l'axe Y
		    direction = glm::normalize(direction);
            m_phi = std::asin(direction.y);
            m_theta = std::acos(direction.z/std::cos(m_phi));
            m_phi *= 180.0/PI;
            m_theta *= 180.0/PI;
		}
		else
		{ // Sinon c'est l'axe Z
		    direction = glm::normalize(direction);
            m_phi = std::asin(direction.z);
            m_theta = std::acos(direction.x/std::cos(m_phi));
            m_phi *= 180.0/PI;
            m_theta *= 180.0/PI;
		}
	}


	Camera::~Camera()
	{
	}


	void Camera::orient(sf::Vector2i position)
	{
		// Récupération des angles
		m_phi -= static_cast<float>(position.y) * m_sensibility;
		m_theta -= static_cast<float>(position.x) * m_sensibility;

		// Limitation de l'angle phi
	    if(m_phi > 89.0f) {
	        m_phi = 89.0f;
	    } else if(m_phi < -89.0f) {
	        m_phi = -89.0f;
	    }

	    // Conversion des angles en radian
	    float phiRadian = m_phi * static_cast<float>(M_PI) / 180.0f;
		float thetaRadian = m_theta * static_cast<float>(M_PI) / 180.0f;

	    // Calcul des coordonnées sphériques
		if(m_verticalAxis.x == 1.0f) { // Si l'axe vertical est l'axe X
		    m_orientation.x = sinf(phiRadian);
		    m_orientation.y = cosf(phiRadian) * cosf(thetaRadian);
		    m_orientation.z = cosf(phiRadian) * sinf(thetaRadian);
		} else if(m_verticalAxis.y == 1.0f) { // Si c'est l'axe Y
		    m_orientation.x = cosf(phiRadian) * sinf(thetaRadian);
		    m_orientation.y = sinf(phiRadian);
		    m_orientation.z = cosf(phiRadian) * cosf(thetaRadian);
		} else { // Sinon c'est l'axe Z
		    m_orientation.x = cosf(phiRadian) * cosf(thetaRadian);
		    m_orientation.y = cosf(phiRadian) * sinf(thetaRadian);
		    m_orientation.z = sinf(phiRadian);
		}

		// Calcul de la normale
		m_sideshift = cross(m_verticalAxis, m_orientation);
		m_sideshift = normalize(m_sideshift);
		m_target = m_position + m_orientation;
	}


	void Camera::move(sf::Vector2f center)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			m_position = m_position + m_orientation * 0.5f;
			m_target = m_position + m_orientation;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			m_position = m_position - m_orientation * 0.5f;
			m_target = m_position + m_orientation;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			m_position = m_position + m_sideshift * 0.5f;
			m_target = m_position + m_orientation;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			m_position = m_position - m_sideshift * 0.5f;
			m_target = m_position + m_orientation;
		}
		orient(sf::Mouse::getPosition(*m_screen) - (sf::Vector2i)center);//m_mouse.getRelativePosition());
	}


	void Camera::lookAt()
	{
		// Actualisation de la vue dans la matrice
	    m_view = glm::lookAt(m_position, m_target, m_verticalAxis);
	}

	glm::mat4& Camera::update(sf::Vector2f screen_center)
	{
	    move(screen_center);
	    lookAt();
	    return m_view;
	}
}
