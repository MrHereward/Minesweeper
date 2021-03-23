#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include "Button.h"
#include "TextButton.h"
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
	TextButton*** Field;

	TextButton* PlayAgainButton{ new TextButton(152, 85, 250, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149), L"Zagraj ponownie", &MainFont, 30, sf::Color(0, 0, 0)) };

	TextButton* EasyButton{ new TextButton(175, 300, 200, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149), L"�atwy", &MainFont, 30, sf::Color(0, 0, 0)) };

	TextButton* MediumButton{ new TextButton(175, 400, 200, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149), L"�redni", &MainFont, 30, sf::Color(0, 0, 0)) };

	TextButton* HardButton{ new TextButton(175, 500, 200, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149), L"Trudny", &MainFont, 30, sf::Color(0, 0, 0)) };

	TextButton* ExitButton{ new TextButton(175, 600, 200, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149), L"Wyjd�", &MainFont, 30, sf::Color(0, 0, 0)) };

	TextButton* ReturnButton{ new TextButton(5, 5, 85, 35, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149), L"Powr�t", &MainFont, 20, sf::Color(0, 0, 0)) };

	//TextField* PlayAgainTextField{ new TextField(L"Zagraj ponownie", 178, 90, 30, &MainFont, sf::Color(0, 0, 0)) };

	TextField* GameStateTextField{ new TextField(157, 20, 50, &MainFont, sf::Color(0, 0, 0)) };

	TextField* MinesweeperTextField{ new TextField(L"Saper", 195, 25, 70, &MainFont, sf::Color(0, 0, 0)) };

	//TextField* DifficultyLevelTextField{ new TextField(L"Wybierz poziom trudno�ci:", 60, 200, 40, &MainFont, sf::Color(0, 0, 0)) };

	//TextField* EasyTextField{ new TextField(L"�atwy", 240, 307, 30, &MainFont, sf::Color(0, 0, 0)) };

	//TextField* MediumTextField{ new TextField(L"�redni", 235, 407, 30, &MainFont, sf::Color(0, 0, 0)) };

	//TextField* HardTextField{ new TextField(L"Trudny", 230, 507, 30, &MainFont, sf::Color(0, 0, 0)) };

	//TextField* ExitTextField{ new TextField(L"Wyjd�", 240, 607, 30, &MainFont, sf::Color(0, 0, 0)) };

	//TextField* ReturnTextField{ new TextField(L"Powr�t", 15, 10, 20, &MainFont, sf::Color(0, 0, 0)) };

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

	~Minesweeper();

	void MainLoop();

	void StartGame();

	void PlantBombs();

	void SetFieldsID();

	void Move(int x, int y);

	void NonunveliedFields();

	void UpdateObjects();

	void DrawObjects();

};