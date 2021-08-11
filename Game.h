#ifndef GAME_H
#define GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>


enum class eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT }; // Controls


struct Snake
{
	sf::RectangleShape snake;
	eDirection direction;
};

/*
	Game engine of sorts
*/
class Game
{
private:
	//Window
	sf::RenderWindow* window;//dynamically allocate to be deleted easily
	sf::VideoMode videomode;
	sf::Event ev;

	//Mouse positions for start screen
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game Objects
	std::vector<Snake> snake;
	sf::RectangleShape fruit;
	sf::RectangleShape clickYes;
	sf::RectangleShape clickNo;
	sf::RectangleShape clickE;
	sf::RectangleShape clickM;
	sf::RectangleShape clickH;

	//Functions
	void initVariables();
	void initWindow();
	void initSnake(float x, float y);
	void initFruit();
	void initYesOrNo();
	void initStartScreen();

public:
	eDirection dir;
	eDirection tmpdir;
	
	//Constructors and Destructors
	Game();
	virtual ~Game();
	
	//Restart the Game
	void gameInit();
	void gameInitWithoutNewWindow();
	void gameInitWithStartScreen();
	void addScore();
	void isPaused();
	void gameOver();
	void openStartScreen();
	

	//Other Screens
	bool gamePaused = false;
	bool isGameOver = false;
	bool restart = false;
	bool startScreen = true;
	bool reset = false;

	//Accessors
	const bool running() const;
	int points = 0;
	int difficulty_value = 0;

	//Functions
	void addSnake(sf::RectangleShape snake1);
	void pollEvents();
	void updateMousePositions();
	void update();
	void render();
};
#endif