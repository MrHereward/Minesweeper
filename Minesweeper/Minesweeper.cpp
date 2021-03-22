#include "Minesweeper.h"

Minesweeper::Minesweeper()
	: Window(sf::VideoMode{ 555, 705 }, "Minesweeper", sf::Style::Close), GameState(GAMESTATE::SELECTION)
{
	RedBombTexture.loadFromFile("Bomb.jpg");
	GrayBombTexture.loadFromFile("Bomb2.jpg");

	Flag.loadFromFile("Flag.jpg");

	MainFont.loadFromFile("Oswald-Bold.ttf");

	TopRectangle->setPosition(sf::Vector2f{ 5, 5 });
	TopRectangle->setSize(sf::Vector2f{ 545, 145 });
	TopRectangle->setFillColor(sf::Color(149, 149, 149));

	Field = { new Button ** [10] };

	for (int i = 0; i < 10; ++i)
	{
		Field[i] = { new Button * [10] };

		for (int j = 0; j < 10; ++j)
		{
			Field[i][j] = { new Button(static_cast<float>(j * 50 + (j + 1) * 5), static_cast<float>(i * 50 + (i + 1) * 5 + 150), 50, 50, sf::Color(110, 110, 110), sf::Color(110, 110, 110), sf::Color(110, 110, 110), sf::Color(110, 110, 110)) };
		}
	}
}

Minesweeper::~Minesweeper()
{
	delete[] Field;
}

void Minesweeper::MainLoop()
{
	srand(static_cast<unsigned int>(time(NULL)));

	sf::Event MainEvent;
	//to do
	TextButton Yes(152, 85, 250, 50, sf::Color(110, 110, 110), sf::Color(149, 149, 149), sf::Color(149, 149, 149), sf::Color(149, 149, 149), L"Tak", 30, &MainFont, sf::Color(0, 0, 0));

	while (Window.isOpen())
	{
		while (Window.pollEvent(MainEvent))
		{
			switch (MainEvent.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			}
		}

		//UpdateObjects();

		Window.clear(sf::Color(61, 61, 61));
		
		//DrawObjects();

		Window.display();
	}
}

void Minesweeper::StartGame()
{
	GameState = { GAMESTATE::NOTSTARTED };

	delete[] Field;

	sf::sleep(sf::milliseconds(200));

	Field = { new Button ** [10] };

	for (int i = 0; i < 10; ++i)
	{
		Field[i] = { new Button * [10] };

		for (int j = 0; j < 10; ++j)
		{
			Field[i][j] = { new Button(static_cast<float>(j * 50 + (j + 1) * 5), static_cast<float>(i * 50 + (i + 1) * 5 + 150), 50, 50, sf::Color(110, 110, 110), sf::Color(110, 110, 110), sf::Color(110, 110, 110), sf::Color(110, 110, 110)) };
		}
	}

	PlantBombs();
	
	//SetFieldsID();
}

void Minesweeper::PlantBombs()
{
	std::vector<std::pair<int, int>> Coordinates;

	bool IsTheSame;

	int x;
	int y;

	for (int i = 0; i < AmountOfBombs; ++i)
	{
		do
		{
			IsTheSame = { false };

			x = { rand() % 10 };
			y = { rand() % 10 };

			for (const auto& Numbers : Coordinates)
			{
				if (Numbers.first == x && Numbers.second == y)
				{
					IsTheSame = { true };
					break;
				}
			}

		} while (IsTheSame);

		Coordinates.push_back(std::make_pair(x, y));

		Field[x][y]->SetID(10);
	}
}
/*
void Minesweeper::SetFieldsID()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (Field[i][j]->GetID() >= 10)
			{
				if (j + 1 <= 9)
				{
					if (i - 1 >= 0)
					{
						Field[i - 1][j + 1]->SetID(Field[i - 1][j + 1]->GetID() + 1);
					}

					Field[i][j + 1]->SetID(Field[i][j + 1]->GetID() + 1);

					if (i + 1 <= 9)
					{
						Field[i + 1][j + 1]->SetID(Field[i + 1][j + 1]->GetID() + 1);
					}
				}

				if (i - 1 >= 0)
				{
					Field[i - 1][j]->SetID(Field[i - 1][j]->GetID() + 1);
				}

				if (i + 1 <= 9)
				{
					Field[i + 1][j]->SetID(Field[i + 1][j]->GetID() + 1);
				}
				
				if (j - 1 >= 0)
				{
					if (i - 1 >= 0)
					{
						Field[i - 1][j - 1]->SetID(Field[i - 1][j - 1]->GetID() + 1);
					}

					Field[i][j - 1]->SetID(Field[i][j - 1]->GetID() + 1);

					if (i + 1 <= 9)
					{
						Field[i + 1][j - 1]->SetID(Field[i + 1][j - 1]->GetID() + 1);
					}
				}
			}
		}
	}

	GameState = { GAMESTATE::MOVE };

}

void Minesweeper::Move(int x, int y)
{
	if (!Field[x][y]->GetIsUnveiled())
	{
		if (Field[x][y]->GetID() >= 10)
		{
			Field[x][y]->SetIsUnveiled(true);

			Field[x][y]->setTexture(&RedBombTexture);
			Field[x][y]->setFillColor(sf::Color::White);

			GameStateTextField->SetString(L"PRZEGRANA");

			GameState = { GAMESTATE::LOSE };

			return;
		}
		else if (Field[x][y]->GetID() != 0)
		{
			Field[x][y]->SetIsUnveiled(true);

			Field[x][y]->setFillColor(sf::Color(149, 149, 149));
			Field[x][y]->SetButtonText(30, &MainFont, std::to_string(Field[x][y]->GetID()), sf::Color(0, 0, 0));
		}
		else
		{
			if (!Field[x][y]->GetIsUnveiled())
			{
				Field[x][y]->SetIsUnveiled(true);

				Field[x][y]->setFillColor(sf::Color(149, 149, 149));

				if (y + 1 <= 9)
				{
					if (x - 1 >= 0)
					{
						Move(x - 1, y + 1);
					}

					Move(x, y + 1);

					if (x + 1 <= 9)
					{
						Move(x + 1, y + 1);
					}
				}

				if (x - 1 >= 0)
				{
					Move(x - 1, y);
				}

				if (x + 1 <= 9)
				{
					Move(x + 1, y);
				}

				if (y - 1 >= 0)
				{
					if (x - 1 >= 0)
					{
						Move(x - 1, y - 1);
					}

					Move(x, y - 1);

					if (x + 1 <= 9)
					{
						Move(x + 1, y - 1);
					}
				}
			}
		}
	}

	NonunveliedFields();

}

void Minesweeper::NonunveliedFields()
{
	int AmountOfNonunveliedFields{};

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (Field[i][j]->GetIsUnveiled() == false)
			{
				++AmountOfNonunveliedFields;
			}
		}
	}

	if (AmountOfNonunveliedFields == AmountOfBombs)
	{
		GameStateTextField->SetString(L"  WYGRANA");

		GameState = { GAMESTATE::WIN };
	}
}

void Minesweeper::UpdateObjects()
{
	switch (GameState)
	{
	case GAMESTATE::WIN:

	case GAMESTATE::LOSE:
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (!Field[i][j]->GetIsUnveiled() && Field[i][j]->GetID() >= 10)
				{
					Field[i][j]->setFillColor(sf::Color::White);
					Field[i][j]->setTexture(&GrayBombTexture);
				}
			}
		}

		if (ReturnButton->UpdateButton(Window) == BUTTONSTATE::LEFTPUSHED)
		{
			GameState = { GAMESTATE::SELECTION };
		}
		
		if (PlayAgainButton->UpdateButton(Window) == BUTTONSTATE::LEFTPUSHED)
		{
			StartGame();
		}

		break;

	case GAMESTATE::MOVE:
		if (PlayAgainButton->UpdateButton(Window) == BUTTONSTATE::LEFTPUSHED)
		{
			StartGame();
		}

		if (ReturnButton->UpdateButton(Window) == BUTTONSTATE::LEFTPUSHED)
		{
			GameState = { GAMESTATE::SELECTION };
		}

		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (!Field[i][j]->GetIsUnveiled())
				{
					if (Field[i][j]->UpdateButton(Window) == BUTTONSTATE::LEFTPUSHED)
					{
						Move(i, j);
					}

					if (Field[i][j]->UpdateButton(Window) == BUTTONSTATE::RIGHTPUSHED)
					{
						if (!Field[i][j]->GetIsFlaged())
						{
							Field[i][j]->setTexture(&Flag);
						}
						else
						{

						}
					}
				}
			}
		}

		break;

	case GAMESTATE::SELECTION:
		if (EasyButton->UpdateButton(Window) == BUTTONSTATE::LEFTPUSHED)
		{
			AmountOfBombs = { 10 };
			StartGame();
		}

		if (MediumButton->UpdateButton(Window) == BUTTONSTATE::LEFTPUSHED)
		{
			AmountOfBombs = { 15 };
			StartGame();
		}

		if (HardButton->UpdateButton(Window) == BUTTONSTATE::LEFTPUSHED)
		{
			AmountOfBombs = { 20 };
			StartGame();
		}

		if (ExitButton->UpdateButton(Window) == BUTTONSTATE::LEFTPUSHED)
		{
			Window.close();
		}
	}
}

void Minesweeper::DrawObjects()
{
	switch (GameState)
	{
	case GAMESTATE::WIN:

	case GAMESTATE::LOSE:
		Window.draw(*TopRectangle);

		Window.draw(*ReturnButton);
		ReturnTextField->Draw(Window);

		Window.draw(*PlayAgainButton);
		PlayAgainTextField->Draw(Window);

		GameStateTextField->Draw(Window);

		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				Window.draw(*Field[i][j]);
				Window.draw(Field[i][j]->GetButtonText());
			}
		}

		break;

	case GAMESTATE::MOVE:
		Window.draw(*TopRectangle);

		Window.draw(*ReturnButton);
		ReturnTextField->Draw(Window);

		Window.draw(*PlayAgainButton);
		PlayAgainTextField->Draw(Window);

		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				Window.draw(*Field[i][j]);
				Window.draw(Field[i][j]->GetButtonText());
			}
		}

		break;

	case GAMESTATE::SELECTION:
		Window.draw(*TopRectangle);
		MinesweeperTextField->Draw(Window);

		DifficultyLevelTextField->Draw(Window);

		Window.draw(*EasyButton);
		EasyTextField->Draw(Window);

		Window.draw(*MediumButton);
		MediumTextField->Draw(Window);

		Window.draw(*HardButton);
		HardTextField->Draw(Window);

		Window.draw(*ExitButton);
		ExitTextField->Draw(Window);

		break;
	}
}*/