#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "Headers.h"
#include "Mouse.h"

namespace Core
{
	class Camera
	{
		public:
			Camera();
			Camera(sf::RenderWindow* screen, glm::vec3 position, glm::vec3 target, glm::vec3 verticalAxis, float sensibility, float speed);
			glm::mat4& update(sf::Vector2f screen_center);
			~Camera();

		private:
			void move(sf::Vector2f center);
			void lookAt();
			void orient(sf::Vector2i position);
			float m_phi, m_theta, m_sensibility, m_speed;
			glm::vec3 m_orientation;
			glm::vec3 m_verticalAxis;
			glm::vec3 m_sideshift;
			glm::vec3 m_position;
			glm::vec3 m_target;
			glm::mat4 m_view;
			Core::Mouse m_mouse;
			sf::RenderWindow* m_screen;
	};
}

#endif //CAMERA_H
