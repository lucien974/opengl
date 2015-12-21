#include "Mouse.h"

namespace Core
{
	Mouse::Mouse(): m_lastPosition(getPosition())
	{
	}


	sf::Vector2i Mouse::getRelativePosition() {
		m_relativePosition.x = 400 - getPosition().x;
		m_relativePosition.y = 300 - getPosition().y;
		m_lastPosition = sf::Vector2i(400, 300);
		return m_relativePosition;
	}
}
