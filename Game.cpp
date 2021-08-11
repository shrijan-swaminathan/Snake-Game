#include "Game.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <vector>  
#include <chrono>
#include <thread>

//Private Functions
void Game::initVariables()
{
	window = nullptr;//initializes pointer to nulffvl
}

void Game::initWindow()//creates the window
{
	videomode.height = 630;
	videomode.width = 800;
	window = new sf::RenderWindow(videomode, "Snake", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
}

void Game::initSnake(float x, float y)//snake head object creation
{

	Snake snake1;
	snake1.direction = dir;
	snake1.snake.setPosition(10.f, 10.f);
	snake1.snake.setSize(sf::Vector2f(x,y));
	snake1.snake.setFillColor(sf::Color::Blue);
	snake1.snake.setOutlineColor(sf::Color::Cyan);
	snake1.snake.setOutlineThickness(1.f);
	snake.push_back(snake1);
}

void Game::initFruit()//add characteristics to a fruit object
{
	srand(time(0));
	fruit.setPosition((float)(rand() % (videomode.width/ 10)) * 10, (float)(rand() % ((videomode.height - 30)/ 10)) * 10);
	fruit.setSize(sf::Vector2f(10.f, 10.f));
	fruit.setFillColor(sf::Color::Red);

}

void Game::initYesOrNo()//creates function for the yes and no boxes in game over screen
{

	clickYes.setPosition(100,400);
	clickYes.setSize(sf::Vector2f(200.f, 100.f));
	clickYes.setFillColor(sf::Color::White);
	clickNo.setPosition(500,400);
	clickNo.setSize(sf::Vector2f(200.f, 100.f));
	clickNo.setFillColor(sf::Color::White);
	updateMousePositions();
}

void Game::initStartScreen()
{
	clickE.setPosition(50, 400);
	clickE.setSize(sf::Vector2f(200.f, 100.f));
	clickE.setFillColor(sf::Color::White);

	clickM.setPosition(300, 400);
	clickM.setSize(sf::Vector2f(200.f, 100.f));
	clickM.setFillColor(sf::Color::White);

	clickH.setPosition(550, 400);
	clickH.setSize(sf::Vector2f(200.f, 100.f));
	clickH.setFillColor(sf::Color::White);
	updateMousePositions();
}

//Constructors and Destructors
Game::Game()//constructor
{
	gameInit();
}

Game::~Game()//destructor
{
	delete window;
}

void Game::gameInit()
{
	snake.clear();//clear normal screen to start game and initialize starting sequences for the game
	initVariables();
	initWindow();
	initSnake(10, 10);
	initFruit();
	dir = eDirection::STOP;
	points = 0;
	addScore();
}

void Game::gameInitWithoutNewWindow()
{
	snake.clear();//clear normal screen to start game and initialize starting sequences for the game
	//initVariables();
	//initWindow();
	initSnake(10, 10);
	initFruit();
	dir = eDirection::STOP;
	points = 0;
	addScore();
}

void Game::gameInitWithStartScreen()
{
	//reset everything
	reset = true;
}

void Game::addScore()
{
	sf::Font font1;
	if (!font1.loadFromFile("Fonts/arial.ttf"))
	{
		throw("COULD NOT LOAD FONT!");
	}

	//Create text
	sf::Text text1;
	text1.setFont(font1);
	text1.setCharacterSize(10);
	//text1.setStyle(sf::Text::Bold);
	text1.setFillColor(sf::Color::White);
	text1.setPosition(10, videomode.height - 15);
	std::string scoreBoard = "Score: " + std::to_string(points);
	text1.setString(scoreBoard);
	window->draw(text1);
}

void Game::isPaused()
{
	// loading font
	sf::Font font;
	if(!font.loadFromFile("Fonts/arial.ttf"))
	{
		throw("COULD NOT LOAD FONT!");
	}

	//Create text
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Black);
	text.setPosition(300, 250);
	text.setString("Paused...");

	window->draw(text);
}

void Game::gameOver()
{
	sf::Font font2;
	if (!font2.loadFromFile("Fonts/arial.ttf"))
	{
		throw("COULD NOT LOAD FONT!");
	}

	//Create text
	sf::Text text2;
	text2.setFont(font2);
	text2.setCharacterSize(50);
	text2.setStyle(sf::Text::Bold);
	text2.setFillColor(sf::Color::White);
	text2.setPosition(75, 150);
	text2.setString("        GAME OVER!\nWould you like to try again?");

	sf::Text yes;
	yes.setFont(font2);
	yes.setCharacterSize(50);
	yes.setStyle(sf::Text::Bold);
	yes.setFillColor(sf::Color::Black);
	yes.setPosition(150, 400);
	yes.setString("Yes");

	sf::Text no;
	no.setFont(font2);
	no.setCharacterSize(50);
	no.setStyle(sf::Text::Bold);
	no.setFillColor(sf::Color::Black);
	no.setPosition(550, 400);
	no.setString("No");

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (clickYes.getGlobalBounds().contains(mousePosView))
		{
			gameInitWithoutNewWindow();
			isGameOver = false;
		}
		if (clickNo.getGlobalBounds().contains(mousePosView))
		{
			gameInitWithStartScreen();
			isGameOver = false;
		}
		else
		{
			window->draw(text2);
			window->draw(clickYes);
			window->draw(clickNo);
			window->draw(yes);
			window->draw(no);
		}
	}
	else
	{
		window->draw(text2);
		window->draw(clickYes);
		window->draw(clickNo);
		window->draw(yes);
		window->draw(no);
	}
}

void Game::openStartScreen()
{
	sf::Font font2;
	if (!font2.loadFromFile("Fonts/arial.ttf"))
	{
		throw("COULD NOT LOAD FONT!");
	}

	//Create text
	sf::Text text2;
	text2.setFont(font2);
	text2.setCharacterSize(50);
	text2.setStyle(sf::Text::Bold);
	text2.setFillColor(sf::Color::Blue);
	text2.setPosition(300, 150);
	text2.setString("SNAKE");

	sf::Text easy;
	easy.setFont(font2);
	easy.setCharacterSize(50);
	easy.setStyle(sf::Text::Bold);
	easy.setFillColor(sf::Color::Black);
	easy.setPosition(80, 400);
	easy.setString("easy");

	sf::Text medium;
	medium.setFont(font2);
	medium.setCharacterSize(50);
	medium.setStyle(sf::Text::Bold);
	medium.setFillColor(sf::Color::Black);
	medium.setPosition(315, 400);
	medium.setString("medium");

	sf::Text hard;
	hard.setFont(font2);
	hard.setCharacterSize(50);
	hard.setStyle(sf::Text::Bold);
	hard.setFillColor(sf::Color::Black);
	hard.setPosition(580, 400);
	hard.setString("hard");

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (clickE.getGlobalBounds().contains(mousePosView))
		{
			difficulty_value = 50;
			gameInitWithoutNewWindow();
			startScreen = false;
		}
		else if (clickM.getGlobalBounds().contains(mousePosView))
		{
			difficulty_value = 25;
			gameInitWithoutNewWindow();
			startScreen = false;
		}
		else if (clickH.getGlobalBounds().contains(mousePosView))
		{
			difficulty_value = 0;
			gameInitWithoutNewWindow();
			startScreen = false;
		}
		else
		{
			window->draw(text2);
			window->draw(clickE);
			window->draw(clickM);
			window->draw(clickH);
			window->draw(easy);
			window->draw(medium);
			window->draw(hard);
		}
	}
	else
	{
		window->draw(text2);
		window->draw(clickE);
		window->draw(clickM);
		window->draw(clickH);
		window->draw(easy);
		window->draw(medium);
		window->draw(hard);
	}
}

//Accessors
const bool Game::running() const//checks if window is running
{
	return window->isOpen();
}

void Game::addSnake(sf::RectangleShape snake1)
{
	Snake x;
	x.direction = dir;
	x.snake = snake1;
	snake.push_back(x);
	int i = snake.size() - 1;
	if (dir == eDirection::UP)
	{
		snake[i].snake.setPosition(snake[i-1].snake.getPosition().x, snake[i-1].snake.getPosition().y + 10);
	}
	if (dir == eDirection::DOWN)
	{
		snake[i].snake.setPosition(snake[i - 1].snake.getPosition().x, snake[i - 1].snake.getPosition().y - 10);
	}
	if (dir == eDirection::LEFT)
	{
		snake[i].snake.setPosition(snake[i - 1].snake.getPosition().x + 10, snake[i - 1].snake.getPosition().y);
	}
	if (dir == eDirection::RIGHT)
	{
		snake[i].snake.setPosition(snake[i - 1].snake.getPosition().x - 10, snake[i - 1].snake.getPosition().y);
	}
	snake[i].snake.setSize(sf::Vector2f(10.f, 10.f));
	snake[i].snake.setFillColor(sf::Color::Green);
	snake[i].snake.setOutlineColor(sf::Color::Magenta);
	snake[i].snake.setOutlineThickness(1.f);
}

//Functions
void Game::pollEvents()//checks events being polled
{
	while (window->pollEvent(ev))//store events into ev
	{
		switch (ev.type)
		{
		case sf::Event::Closed: //exit event polling if window is closed
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (!gamePaused)
			{
				if (ev.key.code == sf::Keyboard::Up)
				{
					dir = eDirection::UP;
				}
				if (ev.key.code == sf::Keyboard::Down)
				{
					dir = eDirection::DOWN;
				}
				if (ev.key.code == sf::Keyboard::Left)
				{
					dir = eDirection::LEFT;
				}
				if (ev.key.code == sf::Keyboard::Right)
				{
					dir = eDirection::RIGHT;
				}
			}
			if (ev.key.code == sf::Keyboard::Escape)
			{
				reset = true;
			}
			if (ev.key.code == sf::Keyboard::End)
			{
				window->close();
			}
			if (ev.key.code == sf::Keyboard::Space)
			{
				gamePaused = !gamePaused;
			}
			snake[0].direction = dir;
			break;
			
		}
	}
}

void Game::updateMousePositions()
{
	//updates mouse positions
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game::update()//updates events
{
	pollEvents();
	if (startScreen)
	{
		initStartScreen();
	}

	auto current = snake[0];
	current.snake.setFillColor(sf::Color::Green);
	current.snake.setOutlineColor(sf::Color::Magenta);

	for (int i = 0; i < snake.size() - 1; i++)
	{
		auto prev = snake[i + 1];
		snake[i + 1] = current;
		current = prev;
	}

	//direction logic
	if (dir == eDirection::UP)
	{
		snake[0].snake.setPosition(snake[0].snake.getPosition().x, snake[0].snake.getPosition().y - 10.f);
	}
	if (dir == eDirection::DOWN)
	{
		snake[0].snake.setPosition(snake[0].snake.getPosition().x, snake[0].snake.getPosition().y + 10.f);
	}
	if (dir == eDirection::LEFT)
	{
		snake[0].snake.setPosition(snake[0].snake.getPosition().x - 10.f, snake[0].snake.getPosition().y);
	}
	if (dir == eDirection::RIGHT)
	{
		snake[0].snake.setPosition(snake[0].snake.getPosition().x + 10.f, snake[0].snake.getPosition().y);
	}

	for(int i = snake.size() - 1; i >= 0; i--)
	{
		//wrapping logic
		if (snake[i].snake.getPosition().x < 0)
		{
			snake[i].snake.setPosition(videomode.width, snake[i].snake.getPosition().y);
		}
		if (snake[i].snake.getPosition().y < 0)
		{
			snake[i].snake.setPosition(snake[i].snake.getPosition().x, videomode.height - 30);
		}
		if (snake[i].snake.getPosition().x > videomode.width)
		{
			snake[i].snake.setPosition(0, snake[i].snake.getPosition().y);
		}
		if (snake[i].snake.getPosition().y > videomode.height - 30)
		{
			snake[i].snake.setPosition(snake[i].snake.getPosition().x, 0);
		}


		//blocking logic
		if (i > 0)
		{
			if (snake[0].snake.getPosition().x == snake[i].snake.getPosition().x && snake[0].snake.getPosition().y == snake[i].snake.getPosition().y)
			{
				dir = eDirection::STOP;
				isGameOver = true;
				initYesOrNo();
				break;
			}
		}
	}



	//change position of fruit when snake hits the same position and add one snake block to the snake
	if (snake[0].snake.getPosition().x == fruit.getPosition().x && snake[0].snake.getPosition().y == fruit.getPosition().y)
	{
		if (difficulty_value == 50)
		{
			points += 100;
		}
		if (difficulty_value == 25)
		{
			points += 200;
		}
		if (difficulty_value == 0)
		{
			points += 400;
		}
		sf::RectangleShape snake1;
		addSnake(snake1);
		fruit.setPosition((float)(rand() % (videomode.width / 10)) * 10, (float)(rand() % ((videomode.height - 30)/ 10)) * 10);
	}
}

void Game::render()//clears frame and renders all objects
{
	std::this_thread::sleep_for(std::chrono::milliseconds(difficulty_value));

	window->clear();
	
	//draw game objects
	for (int i = 0; i < snake.size(); i++)//draw each module of the snake
	{
		window->draw(snake[i].snake);
	}
	window->draw(fruit);//draw the fruit
	addScore();
	if (gamePaused)
	{
		window->clear(sf::Color(168, 168, 168, 255));
		isPaused();
	}
	if(isGameOver)
	{
		window->clear();
		gameOver();
	}
	if (startScreen)
	{
		window->clear();
		openStartScreen();
	}
	window->display();//create the newly rendered frame
}
