#include "stdafx.h"
#include "Guard.h"
#include "ParticleEngine.h"
#include "EntityManager.h"
#include "Projectile.h"
#include "Player.h"

Guard::Guard(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position,Player* player,ParticleEngine* particleEngine):alert_(false),
	player_(player),health_(100),particleEngine_(particleEngine),ideal_dist(5*TILE_SIZE),reload_timer(0),reload_threshold(1000){
	constructEntity(resourceManager, "guard", entityManager, position, true, true, SHAPE_CIRCLE, DYNAMIC_MOVING,TYPE_GUARD);
}

void Guard::fire(sfld::Vector2f dir){
	reload_timer = 0;
	Projectile* projectile = new Projectile(resourceManager_, entityManager_, "projectile", getPosition(), dir, 1.5f, particleEngine_, TYPE_PLAYER, 100);
	entityManager_->addEntity(projectile);
}

void Guard::update(int frameTime){
	reload_timer += frameTime;
	if (player_->isMonster() && canSee(player_)){
		if (!alert_){
			alert_ = true;
			sprite_.setTexture(resourceManager_->get("guard_alert"));
		}
	}
	else if(alert_){
	//	alert_ = false;
	//	sprite_.setTexture(resourceManager_->get("guard"));
	}
	if (alert_){
		sfld::Vector2f disp = sfld::Vector2f(player_->getPosition() - getPosition());
		float dist = disp.length();
		if (dist > ideal_dist){
			sfld::Vector2f dir = disp.normalise();
			move(dir, frameTime, 0.35f);
		}
		else if (dist < ideal_dist){
			sfld::Vector2f dir = -disp.normalise();
			move(dir, frameTime, 0.35f);
		}
		if (reload_timer > reload_threshold){
			fire(disp.normalise());
		}
	}
}

void Guard::damaged(int amount){
	health_ -= amount;
	if (health_ <= 0){
		particleEngine_->generateBloodEffect(getPosition());
		destroy();
	}
}

