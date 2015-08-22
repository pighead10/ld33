#include "stdafx.h"
#include "SwitchBlock.h"
#include "Player.h"

SwitchBlock::SwitchBlock(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position)
	:enabled_(false){
	constructEntity(resourceManager, "switchblock_off", entityManager, position, true, true, SHAPE_SQUARE, DYNAMIC_STATIC, TYPE_WALL);
}

void SwitchBlock::change(){
	if (enabled_){
		sprite_.setTexture(resourceManager_->get("switchblock_off"));
		setWalkthrough(true);
		setSeethrough(true);
		enabled_ = false;
	}
	else{
		sprite_.setTexture(resourceManager_->get("switchblock_on"));
		setWalkthrough(false);
		setSeethrough(false);
		enabled_ = true;
	}
}