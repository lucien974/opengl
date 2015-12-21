#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H

#include "Headers.h"

namespace Textures
{
	enum ID
	{
		TextureTest,
		TextureCount,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef Core::ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif //RESOURCEIDENTIFIERS_H
