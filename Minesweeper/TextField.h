#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class TextField
{
private:
	sf::Text Text;

public:
	TextField(int CharacterSize, const sf::Font* Font, sf::Color TextColor);

	TextField(sf::String String, int CharacterSize, const sf::Font* Font, sf::Color TextColor);

	void SetPosition(int x, int y);

	void Draw(sf::RenderWindow& Window);

	void SetString(sf::String String);

};