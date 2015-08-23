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
	explicit Level(sf::Font* font);
	~Level();

	virtual void sfmlEvent(sf::Event evt);
	virtual void startLevel(EntityManager* entityManager,ResourceManager<sf::Texture,std::string>* resourceManager,ParticleEngine* particleEngine);
	virtual void update(int frameTime);
	virtual void render(sf::RenderTarget* target);
	bool getAdvanceLevel() const;
protected:
	void setGuardText();
	void updateRagebar();

	int levelnum_;
	void constructLevel(sf::Font* font);

	void baseStartLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
	sf::Font* font_;

	bool finished;

	int guard_limit_;
	virtual void won();
	virtual void lost();
	virtual void overkilled();

	sf::RectangleShape lostOverlay;
	sf::Text lostText1;
	sf::Text lostText2;
	sf::Text lostText3;

	sf::RectangleShape killOverlay;
	sf::Text killText1;
	sf::Text killText2;
	sf::Text killText3;
	sf::Text killText4;
	sf::Text killText5;

	sf::Text levelText;
	sf::Text guardText;
	sf::Sprite guardspr;
	sf::Sprite ragebar;
	sf::Sprite rageoutline;

	sf::Sprite monsterbar;

	bool overkill;
	int killTimer;

	sf::Text wonText1;
	sf::Text wonText2;

	sf::Text messageText;

	void displayMessage(std::string text);
	bool disp_message;
	int messageTimer;

	bool gameLost;
	int lostTimer;

	Player* player_;
	Serum* serum_;
	void loadFromImage(std::string textureName);

	EntityManager* entityManager_;
	ResourceManager<sf::Texture, std::string>* resourceManager_;
	ParticleEngine* particleEngine_;
	
	void baseEvents(sf::Event evt);
	bool advance_level_;
};