#include "stdafx.h"
#include "Projectile.h"
#include "ParticleEngine.h"
#include "SoundManager.h"
#include "EntityManager.h"

Projectile::Projectile(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, std::string spriteName, sfld::Vector2f position,
	sfld::Vector2f direction, float speed, ParticleEngine* particleEngine, ENTITY_TYPE target,int damage):
	direction_(direction),speed_(speed),target_(target),particleEngine_(particleEngine),damage_(damage){
	constructEntity(resourceManager, spriteName, entityManager, position, true, true, Entity::SHAPE_SQUARE, Entity::DYNAMIC_MOVING, Entity::TYPE_BULLET);
}

void Projectile::update(int frameTime){
	move(direction_, frameTime, speed_);
}

void Projectile::collided(Entity* other){
	if (other->getType() == TYPE_WALL){
		if (!other->isWalkthrough()){
			entityManager_->screenShake(3.0f, 280);
			SoundManager::play("hit");
			particleEngine_->generateMiniExplosionEffect(getPosition());
			destroy();
		}
	}
	else if (other->getType() == target_){
		entityManager_->screenShake(3.0f, 280);
		other->damaged(damage_);
		SoundManager::play("hit");
		particleEngine_->generateMiniExplosionEffect(getPosition());
		destroy();
	}
}

