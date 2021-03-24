#include "Button.h"

Button::Button(float x, float y, float Width, float Height, sf::Color _IdleColor, sf::Color _HoverColor, sf::Color _LeftColor, sf::Color _RightColor)
	: ButtonState(BUTTONSTATE::IDLE), IsBlocked(false), IsAvailable(true),
	IdleColor(_IdleColor), HoverColor(_HoverColor), LeftColor(_LeftColor), RightColor(_RightColor)
{
	setPosition(x, y);
	setSize(sf::Vector2f{ Width, Height });
	setFillColor(IdleColor);
}

BUTTONSTATE Button::UpdateButton(sf::RenderWindow& Window)
{
	if (IsBlocked)
	{
		return ButtonState;
	}

	ButtonState = { BUTTONSTATE::IDLE };

	if (sf::Mouse::getPosition(Window).x < getPosition().x + getLocalBounds().width &&
		sf::Mouse::getPosition(Window).x > getPosition().x &&
		sf::Mouse::getPosition(Window).y < getPosition().y + getLocalBounds().height &&
		sf::Mouse::getPosition(Window).y > getPosition().y)
	{
		ButtonState = { BUTTONSTATE::HOVER };

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			ButtonState = { BUTTONSTATE::RIGHTPUSHED };
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			ButtonState = { BUTTONSTATE::LEFTPUSHED };
		}
	}

	switch (ButtonState)
	{
	case BUTTONSTATE::IDLE:
		setFillColor(IdleColor);

		break;

	case BUTTONSTATE::HOVER:
		setFillColor(HoverColor);

		break;

	case BUTTONSTATE::LEFTPUSHED:
		setFillColor(LeftColor);

		break;

	case BUTTONSTATE::RIGHTPUSHED:
		setFillColor(RightColor);

		break;
	}

	return ButtonState;
}

void Button::Draw(sf::RenderWindow& Window)
{
	Window.draw(*this);
	Window.draw(ButtonText);
}

void Button::SetID(int _ID)
{
	ID = { _ID };
}

int Button::GetID()
{
	return ID;
}

void Button::SetIsAvailable(bool _IsAvailable)
{
	IsAvailable = { _IsAvailable };
}

bool Button::GetIsAvailable()
{
	return IsAvailable;
}

void Button::SetIsBlocked(bool _IsBlocked)
{
	IsBlocked = { _IsBlocked };
}

bool Button::GetIsBlocked()
{
	return IsBlocked;
}

void Button::SetButtonText(sf::String _String, const sf::Font* MainFont, unsigned int Size, sf::Color ButtonTextColor)
{
	ButtonText.setString(_String);
	ButtonText.setFont(*MainFont);
	ButtonText.setCharacterSize(Size);
	ButtonText.setFillColor(ButtonTextColor);

	ButtonText.setOrigin
	(
		static_cast<int>(ButtonText.getLocalBounds().left + ButtonText.getLocalBounds().width / 2),
		static_cast<int>(ButtonText.getLocalBounds().top + ButtonText.getLocalBounds().height / 2)
	);

	ButtonText.setPosition(static_cast<int>(getPosition().x + getSize().x / 2), static_cast<int>(getPosition().y + getSize().y / 2));
}

sf::Text Button::GetButtonText()
{
	return ButtonText;
}