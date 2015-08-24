#pragma once

#include "Entity.h"

class ParticleEngine;

class Player : public Entity{
public:
	Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position,ParticleEngine* particleEngine);
	void update(int frameTime);

	bool isMonster() const;
	void damaged(int amount);
	bool immune;
	float getMonsterPercent() const;
private:
	bool t2;
	bool transition;
	int transitioncount;
	int transitiontimer;

	void attack();

	void turnIntoMonster();
	void turnIntoNormal();

	enum PlayerState{
		STATE_NORMAL,
		STATE_MONSTER
	};

	int reload_threshold;
	int reload_timer;

	int monster_threshold;
	int move_timer;
	int monster_timer;
	int max_monster;

	int animation_timer;
	int animation_length;
	bool in_animation;

	int health_;

	float speed_;
	PlayerState state_;

	ParticleEngine* particleEngine_;
};