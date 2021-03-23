#pragma once
#include "Button.h"

class TextButton : public Button
{
private:
	sf::Text ButtonText;

	sf::Color ButtonTextColor;

public:
	TextButton() = delete;

	TextButton(float x, float y, float Width, float Height,
		sf::Color _IdleColor, sf::Color _HoverColor, sf::Color _LeftColor, sf::Color _RightColor,
		sf::String _String, const sf::Font* MainFont, unsigned int Size, sf::Color _ButtonTextColor,
		sf::Texture* _LeftTexture = nullptr, sf::Texture* _RightTexture = nullptr);

	void Draw(sf::RenderWindow& Window) override;

	void SetButtonText(sf::String _String, const sf::Font* MainFont, unsigned int Size, sf::Color _ButtonColor);
};