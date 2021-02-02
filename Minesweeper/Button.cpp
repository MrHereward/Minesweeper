#include "Button.h"

Button::Button(float x, float y, float Width, float Height, sf::Color _IdleColor, sf::Color _HoverColor, sf::Color _ActiveColor)
	: ButtonState(BUTTONSTATE::IDLE), IsUnveiled(false),
	IdleColor(_IdleColor), HoverColor(_HoverColor), ActiveColor(_ActiveColor)
{
	setPosition(sf::Vector2f{ x, y });
	setSize(sf::Vector2f{ Width, Height });
}

BUTTONSTATE Button::UpdateButton(sf::RenderWindow& Window)
{
	ButtonState = { BUTTONSTATE::IDLE };

	if (sf::Mouse::getPosition(Window).x < getPosition().x + getLocalBounds().width &&
		sf::Mouse::getPosition(Window).x > getPosition().x &&
		sf::Mouse::getPosition(Window).y < getPosition().y + getLocalBounds().height &&
		sf::Mouse::getPosition(Window).y > getPosition().y)
	{
		ButtonState = { BUTTONSTATE::HOVER };

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			ButtonState = { BUTTONSTATE::ACTIVE };
		}
	}

	switch (ButtonState)
	{
	case BUTTONSTATE::IDLE:
		setFillColor(IdleColor);

		return BUTTONSTATE::IDLE;

	case BUTTONSTATE::HOVER:
		setFillColor(HoverColor);

		return BUTTONSTATE::HOVER;

	case BUTTONSTATE::ACTIVE:
		setFillColor(ActiveColor);

		return BUTTONSTATE::ACTIVE;
	}
}

void Button::SetID(int _ID)
{
	ID = { _ID };
}

int Button::GetID()
{
	return ID;
}

void Button::SetIdleColor(sf::Color _IdleColor)
{
	IdleColor = { _IdleColor };
}

void Button::SetHoverColor(sf::Color _HoverColor)
{
	HoverColor = { _HoverColor };
}

void Button::SetActiveColor(sf::Color _ActiveColor)
{
	ActiveColor = { _ActiveColor };
}

void Button::SetIsUnveiled(bool _IsUnveiled)
{
	IsUnveiled = { _IsUnveiled };
}

bool Button::GetIsUnveiled()
{
	return IsUnveiled;
}

void Button::SetButtonText(int CharacterSize, sf::Font* MainFont, sf::String ButtonString, sf::Color TextColor)
{
	ButtonText.setString(ButtonString);
	ButtonText.setCharacterSize(CharacterSize);
	ButtonText.setFont(*MainFont);
	ButtonText.setFillColor(TextColor);
	ButtonText.setPosition(sf::Vector2f{ getPosition().x + 17, getPosition().y + 7 });
}

sf::Text Button::GetButtonText()
{
	return ButtonText;
}