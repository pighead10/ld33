#include "stdafx.h"
#include "Wall.h"

Wall::Wall(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position){
	constructEntity(resourceManager, "wall", entityManager, position, false, false, SHAPE_SQUARE, DYNAMIC_STATIC,TYPE_WALL);
}