#include "stdafx.h"
#include "MenuState.h"
#include "SoundManager.h"
#include "GameState.h"
#include "StateManager.h"

MenuState::MenuState(){
}

void MenuState::pause(){

}

void MenuState::resume(){

}

void MenuState::exit(){

}

void MenuState::start(){
	resourceManager_.setDirectory("media/images/");
	resourceManager_.load("menuinstructions", "menuinstructions.png");
	resourceManager_.load("menuplay", "menuplay.png");
	resourceManager_.load("instructions", "instructions.png");
	SoundManager::addMusic("menu", "media/music/menumusic.ogg");

	SoundManager::playMusic("menu");

	playscreen = sf::Sprite(resourceManager_.get("menuplay"));
	inscreen = sf::Sprite(resourceManager_.get("menuinstructions"));
	help = sf::Sprite(resourceManager_.get("instructions"));
	helpdisplay = false;
	playselected = true;
}

void MenuState::sfmlEvent(sf::Event evt){
	using namespace sf;
	if (evt.type == Event::KeyPressed){
		if (evt.key.code == Keyboard::W || evt.key.code == Keyboard::Up || evt.key.code == Keyboard::D || evt.key.code == Keyboard::Down){
			playselected = !playselected;
		}
		else if (evt.key.code == Keyboard::Return){
			if (helpdisplay){
				helpdisplay = false;
			}
			else if (!playselected){
				helpdisplay = true;
			}
			else{
				getParent().push(new GameState());
			}
		}
	}
	else if (evt.type == Event::Closed){
		getParent().pop();
	}
}

void MenuState::update(int frameTime){

}

void MenuState::render(sf::RenderTarget* target){
	if (helpdisplay){
		target->draw(help);
	}
	else if (playselected){
		target->draw(playscreen);
	}
	else{
		target->draw(inscreen);
	}
}