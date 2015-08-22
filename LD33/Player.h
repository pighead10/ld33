#pragma once

#include "Entity.h"

class Player : public Entity{
public:
	Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position);
	void update(int frameTime);

	bool isMonster() const;
private:
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
	float speed_;
	PlayerState state_;
};