#pragma once

#include "stdafx.h"

#define TILE_SIZE 32

class Entity;

typedef std::vector<std::unique_ptr<Entity>> EntityList;

class EntityManager{
public:
	EntityManager();
	~EntityManager();

	void addEntity(Entity* entity);
	EntityList* getEntities();

	void update(int frametime);
	void render(sf::RenderTarget* target);

	void clear();

	static sfld::Vector2f convertCoords(sfld::Vector2f tile);

	void screenShake(float magnitude, int time);

	void guardDied();
	int getDeadGuards() const;
private:
	int deadGuards;

	sf::View view;
	int shake_timer;
	bool in_shake;
	int shake_length;
	float shake_magnitude;

	EntityList push_queue_;
	EntityList entities_;
};