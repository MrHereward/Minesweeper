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
	sf::Texture* LeftTexture;
	sf::Texture* RightTexture;

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

	Button(float x, float y, float Width, float Height, sf::Color _IdleColor, sf::Color _HoverColor, sf::Color _LeftColor, sf::Color _RightColor, sf::Texture* _LeftTexture = nullptr, sf::Texture* _RightTexture = nullptr);

	virtual BUTTONSTATE UpdateButton(sf::RenderWindow& Window);

	virtual void Draw(sf::RenderWindow& Window);

	void SetID(int _ID);

	int GetID();

	void SetIsAvailable(bool _IsAvailable);

	bool GetIsAvailable();

	void SetIsBlocked(bool _IsBlocked);

	bool GetIsBlocked();

};