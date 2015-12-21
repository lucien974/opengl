#ifndef MOUSE_H
#define MOUSE_H

#include "Headers.h"

namespace Core
{
	class Mouse: sf::Mouse
	{
		public:
			Mouse();
			sf::Vector2i getRelativePosition();

		private:
			sf::Vector2i m_lastPosition;
			sf::Vector2i m_relativePosition;
	};
}

#endif //MOUSE_H
