#include "TextButton.h"
//to do
TextButton::TextButton(float x, float y, float Width, float Height,
	sf::Color _IdleColor, sf::Color _HoverColor, sf::Color _LeftColor, sf::Color _RightColor,
	sf::String _String, sf::Font& MainFont, unsigned int Size, sf::Color _ButtonTextColor,
	sf::Texture* _LeftTexture = nullptr, sf::Texture* _RightTexture = nullptr)
	: Button(x, y, Width, Height, _IdleColor, _HoverColor, _LeftColor, _RightColor, _LeftTexture, _RightTexture),
	ButtonTextColor(_ButtonTextColor)
{
	ButtonText.setString(_String);
	ButtonText.setFont(MainFont);
	ButtonText.setCharacterSize(Size);
	ButtonText.setFillColor(ButtonTextColor);

	sf::FloatRect RectangleBounds = getGlobalBounds();
	sf::FloatRect TextBounds = ButtonText.getGlobalBounds();

	ButtonText.setPosition
	(
		RectangleBounds.left + (RectangleBounds.width / 2) - (TextBounds.width / 2),
		RectangleBounds.top + (RectangleBounds.height / 2) - (TextBounds.height / 2)
	);

	ButtonText.setFillColor(ButtonTextColor);
}

void TextButton::Draw(sf::RenderWindow& Window)
{
	Window.draw(*this);
	Window.draw(ButtonText);
}