#pragma once

#include "stdafx.h"
#include "ResourceManager.h"

class EntityManager;
class Player;
class ParticleEngine;
class Serum;

class Level{
public:
	Level();
	~Level();

	virtual void sfmlEvent(sf::Event evt);
	virtual void startLevel(EntityManager* entityManager,ResourceManager<sf::Texture,std::string>* resourceManager,ParticleEngine* particleEngine);
	virtual void update(int frameTime);
	virtual void render(sf::RenderTarget* target);
	bool getAdvanceLevel() const;
protected:
	int guard_limit_;
	virtual void won();
	Player* player_;
	Serum* serum_;
	void loadFromImage(std::string textureName);

	EntityManager* entityManager_;
	ResourceManager<sf::Texture, std::string>* resourceManager_;
	ParticleEngine* particleEngine_;
	
	void baseEvents(sf::Event evt);
	bool advance_level_;
};