#pragma once

#include "BaseState.h"

#include "ResourceManager.h"

class EntityManager;
class ParticleEngine;
class Level;

typedef std::vector<std::unique_ptr<Level>> LevelList;

class GameState : public BaseState{
public:
	GameState();
	~GameState();
	void sfmlEvent(sf::Event evt);
	void start();
	void pause();
	void resume();
	void exit();

	void update(int frameTime);
	void render(sf::RenderTarget* target);
private:
	void advanceLevel();

	LevelList levels_;
	int levelnum_;
	Level* currentLevel_;

	ResourceManager<sf::Texture, std::string> resourceManager_;
	std::unique_ptr<EntityManager> entityManager_;
	std::unique_ptr<ParticleEngine> particleEngine_;
};