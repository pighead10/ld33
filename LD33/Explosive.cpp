#include "stdafx.h"
#include "Explosive.h"
#include "ParticleEngine.h"
#include "EntityManager.h"
#include "SoundManager.h"

Explosive::Explosive(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position, ParticleEngine* particleEngine)
	:particleEngine_(particleEngine){
	constructEntity(resourceManager, "explosive", entityManager, position, false, true, SHAPE_SQUARE, DYNAMIC_STATIC, TYPE_WALL);
}

void Explosive::collided(Entity* other){

	if (other->getType() == TYPE_BULLET){
		entityManager_->screenShake(10.0, 750);
		SoundManager::play("explosion");
		particleEngine_->generateExplosionEffect(getPosition());
		EntityList* list = entityManager_->getEntities();
		for (auto& it : *list){
			if (sfld::Vector2f(getPosition() - it->getPosition()).length() <= TILE_SIZE*3.0f){
				it->damaged(200);
			}
		}
		destroy();
	}
}