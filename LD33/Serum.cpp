#include "stdafx.h"
#include "Serum.h"

Serum::Serum(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position):collected_(false){
	constructEntity(resourceManager, "serum", entityManager, position, true, true, SHAPE_CIRCLE, DYNAMIC_STATIC, TYPE_SERUM);
}

bool Serum::hasCollected() const{
	return collected_;
}

void Serum::collided(Entity* other){
	if (other->getType() == TYPE_PLAYER){
		collected_ = true;
	}
}