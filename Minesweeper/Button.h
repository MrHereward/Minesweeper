#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum class BUTTONSTATE : char
{
	IDLE,
	HOVER,
	ACTIVE
};

class Button : public sf::RectangleShape
{
private:
	sf::Text ButtonText{};

	sf::Color IdleColor;
	sf::Color HoverColor;
	sf::Color ActiveColor;

	int ID{};

	BUTTONSTATE ButtonState;

	bool IsUnveiled;

public:
	Button(float x, float y, float Width, float Height, sf::Color _IdleColor, sf::Color _HoverColor, sf::Color _ActiveColor);

	void SetID(int _ID);

	int GetID();

	void SetIdleColor(sf::Color _IdleColor);

	void SetHoverColor(sf::Color _HoverColor);

	void SetActiveColor(sf::Color _ActiveColor);

	BUTTONSTATE UpdateButton(sf::RenderWindow& Window);

	void SetIsUnveiled(bool _IsUnveiled);

	bool GetIsUnveiled();

	void SetButtonText(int CharacterSize, sf::Font* MainFont, sf::String ButtonString, sf::Color TextColor);

	sf::Text GetButtonText();

};