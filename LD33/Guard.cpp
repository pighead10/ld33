#include "stdafx.h"
#include "Guard.h"
#include "ParticleEngine.h"
#include "EntityManager.h"
#include "Projectile.h"
#include "Player.h"
#include "SoundManager.h"

Guard::Guard(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position, Player* player, ParticleEngine* particleEngine, std::vector<std::pair<sfld::Vector2f, int>> dirList) :alert_(false),
	player_(player),health_(100),particleEngine_(particleEngine),ideal_dist(5*TILE_SIZE),reload_timer(200),reload_threshold(500),speed_(0.25f),dirList_(dirList),dirnum_(0),dirtimer_(0){
	constructEntity(resourceManager, "guard", entityManager, position, true, true, SHAPE_CIRCLE, DYNAMIC_MOVING,TYPE_GUARD);
}

void Guard::fire(sfld::Vector2f dir){
	SoundManager::play("shoot");
	reload_timer = 0;
	Projectile* projectile = new Projectile(resourceManager_, entityManager_, "projectile", getPosition(), dir, 1.5f, particleEngine_, TYPE_PLAYER, 100);
	entityManager_->addEntity(projectile);
}

void Guard::update(int frameTime){
	dirtimer_ += frameTime;
	
	if (!alert_ && player_->isMonster() && canSee(player_)){
		alert_ = true;
		sprite_.setTexture(resourceManager_->get("guard_alert"));
	}
	else if(alert_){
	//	alert_ = false;
	//	sprite_.setTexture(resourceManager_->get("guard"));
	}
	if (alert_){
		reload_timer += frameTime;
		sfld::Vector2f disp = sfld::Vector2f(player_->getPosition() - getPosition());
		float dist = disp.length();
		if (dist > ideal_dist){
			sfld::Vector2f dir = disp.normalise();
			move(dir, frameTime, speed_);
		}
		else if (dist < ideal_dist){
			sfld::Vector2f dir = -disp.normalise();
			move(dir, frameTime, speed_);
		}
		if (reload_timer > reload_threshold){
			fire(disp.normalise());
		}
	}
	else{
		if (dirnum_ >= dirList_.size()){
			dirnum_ = 0;
		}
		if (dirnum_ < dirList_.size()){
			move(dirList_[dirnum_].first, frameTime, speed_);
			if (dirtimer_ >= dirList_[dirnum_].second){
				dirnum_++;
				dirtimer_ = 0;
			}
		}
	}
}

void Guard::damaged(int amount){
	health_ -= amount;
	if (health_ <= 0){
	SoundManager::play("enemydead");
		particleEngine_->generateBloodEffect(getPosition());
		entityManager_->guardDied();
		destroy();
	}
}

