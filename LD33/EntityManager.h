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
private:
	EntityList push_queue_;

	EntityList entities_;
};