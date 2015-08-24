#include "stdafx.h"
#include "Switch.h"
#include "Player.h"
#include "EntityManager.h"
#include "SwitchBlock.h"
#include "SoundManager.h"

Switch::Switch(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position, std::vector<SwitchBlock*> connected_entities,Player* player)
:connected_blocks_(connected_entities),enabled_(false),player_(player){
	constructEntity(resourceManager, "switch_off", entityManager, position, true, true, SHAPE_SQUARE, DYNAMIC_STATIC, TYPE_SWITCH);
}

void Switch::change(){
	for (auto& it : connected_blocks_){
		it->change();
	}
	enabled_ = !enabled_;
	if (enabled_){
		SoundManager::play("switchon");
		sprite_.setTexture(resourceManager_->get("switch_on"));
	}
	else{
		SoundManager::play("switchoff");
		sprite_.setTexture(resourceManager_->get("switch_off"));
	}
}

void Switch::update(int frametime){
	if (sfld::Vector2f(player_->getPosition() - getPosition()).length() <= TILE_SIZE){
		if (!stood_){
			stood_ = true;
			change();
		}
	}
	else{
		stood_ = false;
	}
}

