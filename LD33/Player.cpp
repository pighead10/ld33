#include "stdafx.h"
#include "Player.h"
#include "EntityManager.h"
#include "ParticleEngine.h"
#include "SoundManager.h"

Player::Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position,ParticleEngine* particleEngine) :speed_(0.f),
move_timer(0), monster_threshold(1536), state_(STATE_NORMAL),max_monster(3000),reload_timer(0),reload_threshold(750),animation_timer(0),animation_length(500),in_animation(false),
health_(100),particleEngine_(particleEngine){
	constructEntity(resourceManager, "player", entityManager, position, true, true, SHAPE_CIRCLE, DYNAMIC_MOVING,TYPE_PLAYER);
	turnIntoNormal();
	immune = false;
	transition = false;
	transitioncount = 0;
	transitiontimer = 0;
	t2 = false;
}

float Player::getMonsterPercent() const{
	if (!isMonster()){
		return (move_timer / (float)monster_threshold);
	}
	else{
		int n = max_monster - monster_timer;
		return (n/(float)max_monster);
	}
}

void Player::damaged(int amount){
	if (!immune){
		health_ -= amount;
		if (health_ <= 0){
			entityManager_->screenShake(7.0, 850);
			SoundManager::play("died");
			particleEngine_->generateExplosionEffect(getPosition());
			particleEngine_->generateBloodEffect(getPosition());
			entityManager_->playerDied();
			destroy();
		}
	}
}

void Player::turnIntoMonster(){
	SoundManager::play("intomonster");
	monster_timer = 0;
	state_ = STATE_MONSTER;
	transitioncount = 0;
	transitiontimer = 0;
	t2 = false;
	transition = true;
	//sprite_.setTexture(resourceManager_->get("player_monster"),true);
	sprite_.setTexture(resourceManager_->get("transition1"), true);
	centreOrigin();
	speed_ = 0.35f;
}

bool Player::isMonster() const{
	return (state_ == STATE_MONSTER);
}

void Player::turnIntoNormal(){
	SoundManager::play("intohuman");
	transitioncount = 0;
	transitiontimer = 0;
	t2 = false;
	transition = true;
	//sprite_.setTexture(resourceManager_->get("player_monster"),true);
	sprite_.setTexture(resourceManager_->get("transition1"), true);
	speed_ = 0.25f;
	move_timer = 0;
	state_ = STATE_NORMAL;
	sprite_.setTexture(resourceManager_->get("player"),true);
	centreOrigin();
}

void Player::attack(){
	if (reload_timer >= reload_threshold){
		SoundManager::play("attack");
		rotating_ = true;
		entityManager_->screenShake(5.0f, 600);
		sprite_.setTexture(resourceManager_->get("player_attacking"), true);
		centreOrigin();
		in_animation = true;
		animation_timer = 0;
		reload_timer = 0;
		float range = 80.0f;
		EntityList* entities = entityManager_->getEntities();
		for (auto& it : *entities){
			if (it.get() != this){
				float dist = sfld::Vector2f(it->getPosition() - getPosition()).length();
				if (dist <= range){
					it->damaged(100);
				}
			}
		}
	}
}

void Player::update(int frameTime){
	using namespace sf;
	sfld::Vector2f dir(0, 0);
	reload_timer += frameTime;

	if (transition){
		transitiontimer += frameTime;
		if (transitiontimer >= 80){
			transitioncount++;
			if (!t2){
				t2 = true;
				sprite_.setTexture(resourceManager_->get("transition2"), true);
				centreOrigin();
			}
			else{
				t2 = false;
				sprite_.setTexture(resourceManager_->get("transition1"), true);
				centreOrigin();
			}
		}
		if (transitiontimer >= 500){
			if (state_ == STATE_MONSTER){
				sprite_.setTexture(resourceManager_->get("player_monster"), true);
				centreOrigin();
			}
			else if (state_ == STATE_NORMAL){
				sprite_.setTexture(resourceManager_->get("player"), true);
				centreOrigin();
			}
		}
	}
	
	if (Keyboard::isKeyPressed(Keyboard::W)){
		dir.y -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)){
		dir.y += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)){
		dir.x -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)){
		dir.x += 1;
	}
	dir = dir.normalise();
	if (state_ == STATE_NORMAL){
		sfld::Vector2f oldpos = getPosition();
		move(dir, frameTime, speed_);
		sfld::Vector2f newpos = getPosition();
		if (newpos != oldpos){
			//moved!
			move_timer += frameTime;
		}
		if (move_timer >= monster_threshold){
			turnIntoMonster();
		}
	}
	else if (state_ == STATE_MONSTER){
		move(dir, frameTime, speed_);
		monster_timer += frameTime;
		if (monster_timer >= max_monster){
			turnIntoNormal();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			attack();
		}
	}
	if (in_animation){
		animation_timer += frameTime;
		sprite_.rotate(10);
		if (animation_timer >= animation_length){
			if (state_ == STATE_MONSTER){
				sprite_.setTexture(resourceManager_->get("player_monster"), true);
			}
			else{
				sprite_.setTexture(resourceManager_->get("player"), true);
			}
			rotating_ = false;
			centreOrigin();
			in_animation = false;
		}
	}
}