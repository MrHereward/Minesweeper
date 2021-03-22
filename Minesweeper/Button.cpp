#include "Button.h"

Button::Button(float x, float y, float Width, float Height, sf::Color _IdleColor, sf::Color _HoverColor, sf::Color _LeftColor, sf::Color _RightColor, sf::Texture* _LeftTexture, sf::Texture* _RightTexture)
	: ButtonState(BUTTONSTATE::IDLE), IsBlocked(false), IsAvailable(true),
	IdleColor(_IdleColor), HoverColor(_HoverColor), LeftColor(_LeftColor), RightColor(_RightColor),
	LeftTexture(_LeftTexture), RightTexture(_RightTexture)
{
	setPosition(sf::Vector2f{ x, y });
	setSize(sf::Vector2f{ Width, Height });
	setFillColor(IdleColor);
}

BUTTONSTATE Button::UpdateButton(sf::RenderWindow& Window)
{
	if (!IsAvailable || IsBlocked)
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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			ButtonState = { BUTTONSTATE::LEFTPUSHED };
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			ButtonState = { BUTTONSTATE::RIGHTPUSHED };
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
		if (LeftTexture)
		{
			setTexture(LeftTexture);
		}
		else
		{
			setFillColor(LeftColor);
		}

		break;

	case BUTTONSTATE::RIGHTPUSHED:
		if (RightTexture)
		{
			setTexture(RightTexture);
		}
		else
		{
			setFillColor(RightColor);
		}

		break;
	}

	return ButtonState;
}

void Button::Draw(sf::RenderWindow& Window)
{
	Window.draw(*this);
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
	IsAvailable = { IsAvailable };
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