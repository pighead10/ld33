#pragma once

#include "stdafx.h"
#include "ResourceManager.h"

#define TILE_SIZE 32

class Entity;
class ParticleEngine;

typedef std::vector<std::unique_ptr<Entity>> EntityList;


class EntityManager{
public:
	EntityManager(ResourceManager<sf::Texture,std::string>* resourceManager);
	~EntityManager();

	void addEntity(Entity* entity);
	EntityList* getEntities();

	void update(int frametime);
	void render(sf::RenderTarget* target,ParticleEngine* particleEngine);

	void clear();

	static sfld::Vector2f convertCoords(sfld::Vector2f tile);

	void screenShake(float magnitude, int time);

	void guardDied();
	int getDeadGuards() const;
	void playerDied();
	bool isPlayerDead() const;
private:
	ResourceManager<sf::Texture, std::string>* resourceManager_;
	sf::RenderTexture background;
	bool playerDead;
	int deadGuards;

	sf::View view;
	int shake_timer;
	bool in_shake;
	int shake_length;
	float shake_magnitude;

	EntityList push_queue_;
	EntityList entities_;
};