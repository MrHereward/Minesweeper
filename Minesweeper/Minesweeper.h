#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <set>
#include <string>
#include "Button.h"
#include "TextField.h"

enum class GAMESTATE : unsigned char
{
	NOTSTARTED,
	SELECTION,
	MOVE,
	WIN,
	LOSE,
};

class Minesweeper
{
private:
	Button*** Field{};

	Button* PlayAgainButton{ new Button(152, 85, 250, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149)) };

	Button* EasyButton{ new Button(175, 300, 200, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149)) };

	Button* MediumButton{ new Button(175, 400, 200, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149)) };

	Button* HardButton{ new Button(175, 500, 200, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149)) };

	Button* ExitButton{ new Button(175, 600, 200, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149)) };

	Button* ReturnButton{ new Button(5, 5, 85, 35, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149)) };

	TextField* GameStateTextField{ new TextField(50, &MainFont, sf::Color(0, 0, 0)) };

	TextField* MinesweeperTextField{ new TextField(L"Minesweeper", 70, &MainFont, sf::Color(0, 0, 0)) };

	TextField* DifficultyLevelTextField{ new TextField(L"Choose difficulty level:", 40, &MainFont, sf::Color(110, 110, 110)) };

	unsigned int WindowWidth;
	unsigned int WindowHeight;

	sf::RenderWindow Window;

	sf::RectangleShape* TopRectangle{ new sf::RectangleShape() };

	sf::Font MainFont;

	sf::Texture RedBombTexture;
	sf::Texture GrayBombTexture;

	sf::Texture Flag;

	int AmountOfBombs{};

	GAMESTATE GameState;

public:
	Minesweeper();

	void MainLoop();

	void StartGame();

	void PlantBombs();

	void SetFieldsID();

	void Move(int x, int y);

	void UnblockedFields();

	void UpdateObjects();

	void DrawObjects();

};