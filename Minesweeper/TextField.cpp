#include "TextField.h"

TextField::TextField(int CharacterSize, const sf::Font* Font, sf::Color TextColor)
{
	Text.setCharacterSize(CharacterSize);
	Text.setFont(*Font);
	Text.setFillColor(TextColor);
}

TextField::TextField(sf::String String, int CharacterSize, const sf::Font* Font, sf::Color TextColor)
	: TextField(CharacterSize, Font, TextColor)
{
	Text.setString(String);
}

void TextField::SetPosition(int x, int y)
{
	Text.setOrigin
	(
		static_cast<int>(Text.getLocalBounds().left + Text.getLocalBounds().width / 2),
		static_cast<int>(Text.getLocalBounds().top + Text.getLocalBounds().height / 2)
	);

	Text.setPosition(x, y);
}

void TextField::Draw(sf::RenderWindow& Window)
{
	Window.draw(Text);
}

void TextField::SetString(sf::String String)
{
	Text.setString(String);

	SetPosition(Text.getPosition().x, Text.getPosition().y);
}