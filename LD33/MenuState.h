#pragma once

#include "BaseState.h"
#include "ResourceManager.h"

class MenuState : public BaseState{
public:
	MenuState();
	~MenuState();
	void sfmlEvent(sf::Event evt);
	void start();
	void pause();
	void resume();
	void exit();

	void update(int frameTime);
	void render(sf::RenderTarget* target);
private:
	sf::Sprite playscreen;
	sf::Sprite inscreen;
	
	bool playselected;
	sf::Sprite help;
	bool helpdisplay;

	ResourceManager<sf::Texture, std::string> resourceManager_;
};