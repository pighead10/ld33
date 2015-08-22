#include "stdafx.h"
#include "Guard.h"

Guard::Guard(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position,Entity* player):alert_(false),player_(player){
	constructEntity(resourceManager, "guard", entityManager, position, true, true, SHAPE_CIRCLE, DYNAMIC_MOVING);
}

void Guard::update(int frameTime){
	if (canSee(player_)){
		if (!alert_){
			alert_ = true;
			sprite_.setTexture(resourceManager_->get("guard_alert"));
		}
	}
	else if(alert_){
		alert_ = false;
		sprite_.setTexture(resourceManager_->get("guard"));
	}
}

