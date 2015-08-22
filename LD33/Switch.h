#pragma once

#include "Entity.h"

class SwitchBlock;
class Player;

class Switch : public Entity{
public:
	Switch(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position, std::vector<SwitchBlock*> connected_blocks,Player* player);
	void update(int frameTime);
	void change();
private:
	bool stood_;
	bool enabled_;
	Player* player_;
	std::vector<SwitchBlock*> connected_blocks_;
};