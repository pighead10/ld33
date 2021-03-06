#pragma once

#include "Entity.h"

class ParticleEngine;
class Player;

class Guard : public Entity{
public:
	Guard(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position, Player* player, ParticleEngine* particleEngine, std::vector<std::pair<sfld::Vector2f, int>> dirList = std::vector<std::pair<sfld::Vector2f, int>>());
	void update(int frameTime);
	void damaged(int amount);
private:
	void fire(sfld::Vector2f direction);

	int health_;
	bool alert_;
	Player* player_;
	ParticleEngine* particleEngine_;

	int reload_timer;
	int reload_threshold;
	float ideal_dist;

	std::vector<std::pair<sfld::Vector2f, int>> dirList_;
	int dirnum_;
	int dirtimer_;

	float speed_;
};