#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum class BUTTONSTATE : unsigned char
{
	IDLE,
	HOVER,
	LEFTPUSHED,
	RIGHTPUSHED
};

class Button : public sf::RectangleShape
{
protected:
	sf::Text ButtonText{};

	sf::Color IdleColor;
	sf::Color HoverColor;
	sf::Color LeftColor;
	sf::Color RightColor;

	int ID{};

	BUTTONSTATE ButtonState;

	bool IsBlocked;
	bool IsAvailable;

public:
	Button() = delete;

	Button(float x, float y, float Width, float Height, sf::Color _IdleColor, sf::Color _HoverColor, sf::Color _LeftColor = sf::Color(255, 255, 255), sf::Color _RightColor = sf::Color(255, 255, 255));

	BUTTONSTATE UpdateButton(sf::RenderWindow& Window);

	void Draw(sf::RenderWindow& Window);

	void SetID(int _ID);

	int GetID();

	void SetIsAvailable(bool _IsAvailable);

	bool GetIsAvailable();

	void SetIsBlocked(bool _IsBlocked);

	bool GetIsBlocked();

	void SetButtonText(sf::String _String, const sf::Font* MainFont, unsigned int Size, sf::Color ButtonTextColor);

	sf::Text GetButtonText();
};