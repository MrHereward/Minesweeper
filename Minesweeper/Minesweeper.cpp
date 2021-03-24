#include "Minesweeper.h"

Minesweeper::Minesweeper()
	: WindowWidth(550), WindowHeight(700), Window(sf::VideoMode{ WindowWidth, WindowHeight }, "Minesweeper", sf::Style::Close), GameState(GAMESTATE::SELECTION)
{
	RedBombTexture.loadFromFile("Bomb.jpg");
	GrayBombTexture.loadFromFile("Bomb2.jpg");

	Flag.loadFromFile("Flag.jpg");

	MainFont.loadFromFile("Oswald-Bold.ttf");

	TopRectangle->setPosition(sf::Vector2f{ 5, 5 });
	TopRectangle->setSize(sf::Vector2f{ 545, 145 });
	TopRectangle->setFillColor(sf::Color(149, 149, 149));

	PlayAgainButton->SetButtonText(L"Play again", &MainFont, 30, sf::Color(0, 0, 0));
	EasyButton->SetButtonText(L"Easy", &MainFont, 30, sf::Color(0, 0, 0));
	MediumButton->SetButtonText(L"Medium", &MainFont, 30, sf::Color(0, 0, 0));
	HardButton->SetButtonText(L"Hard", &MainFont, 30, sf::Color(0, 0, 0));
	ExitButton->SetButtonText(L"Exit", &MainFont, 30, sf::Color(0, 0, 0));
	ReturnButton->SetButtonText(L"Return", &MainFont, 20, sf::Color(0, 0, 0));

	GameStateTextField->SetPosition(WindowWidth / 2, 50);
	MinesweeperTextField->SetPosition(WindowWidth / 2, 80);
	DifficultyLevelTextField->SetPosition(WindowWidth / 2, 200);
}

void Minesweeper::MainLoop()
{
	srand(static_cast<unsigned int>(time(NULL)));

	sf::Event MainEvent;

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

		UpdateObjects();

		Window.clear(sf::Color(61, 61, 61));

		DrawObjects();

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
	
	SetFieldsID();
}

void Minesweeper::PlantBombs()
{
	std::set<std::pair<int, int>> FieldsWithBomb;

	while (FieldsWithBomb.size() != AmountOfBombs)
	{
		FieldsWithBomb.insert(std::make_pair(rand() % 10, rand() % 10));
	}

	for (const auto& Element : FieldsWithBomb)
	{
		Field[Element.first][Element.second]->SetID(10);
	}
}

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
	if (!Field[x][y]->GetIsBlocked())
	{
		if (Field[x][y]->GetID() >= 10)
		{
			Field[x][y]->SetIsBlocked(true);

			Field[x][y]->setTexture(&RedBombTexture);
			Field[x][y]->setFillColor(sf::Color(255, 255, 255));

			GameStateTextField->SetString(L"You lost");

			GameState = { GAMESTATE::LOSE };

			return;
		}
		else if (Field[x][y]->GetID() != 0)
		{
			Field[x][y]->SetIsBlocked(true);

			Field[x][y]->setFillColor(sf::Color(149, 149, 149));
			Field[x][y]->SetButtonText(std::to_wstring(Field[x][y]->GetID()), &MainFont, 30, sf::Color(0, 0, 0));
		}
		else
		{
			if (!Field[x][y]->GetIsBlocked())
			{
				Field[x][y]->SetIsBlocked(true);

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

	UnblockedFields();

}

void Minesweeper::UnblockedFields()
{
	int AmountOfUnblockedFields{};

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (Field[i][j]->GetIsBlocked() == false)
			{
				++AmountOfUnblockedFields;
			}
		}
	}

	if (AmountOfUnblockedFields == AmountOfBombs)
	{
		GameStateTextField->SetString(L"You won");

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
				if (Field[i][j]->getTexture() == &Flag)
				{
					Field[i][j]->setTexture(nullptr);
				}

				if (!Field[i][j]->GetIsBlocked() && Field[i][j]->GetID() >= 10)
				{
					Field[i][j]->setFillColor(sf::Color(255, 255, 255));
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
				if (!Field[i][j]->GetIsBlocked())
				{
					if (Field[i][j]->GetIsAvailable())
					{
						if (Field[i][j]->UpdateButton(Window) == BUTTONSTATE::LEFTPUSHED)
						{
							Move(i, j);
						}
					}

					if (Field[i][j]->UpdateButton(Window) == BUTTONSTATE::RIGHTPUSHED)
					{
						if (Field[i][j]->GetIsAvailable())
						{
							Field[i][j]->setTexture(&Flag);
							Field[i][j]->SetIsAvailable(false);

							sf::sleep(sf::milliseconds(200));
						}
						else
						{
							Field[i][j]->setTexture(nullptr);
							Field[i][j]->SetIsAvailable(true);

							sf::sleep(sf::milliseconds(200));
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

		ReturnButton->Draw(Window);
		PlayAgainButton->Draw(Window);

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

		ReturnButton->Draw(Window);
		PlayAgainButton->Draw(Window);

		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				Field[i][j]->Draw(Window);
			}
		}

		break;

	case GAMESTATE::SELECTION:
		Window.draw(*TopRectangle);
		MinesweeperTextField->Draw(Window);

		DifficultyLevelTextField->Draw(Window);

		EasyButton->Draw(Window);
		MediumButton->Draw(Window);
		HardButton->Draw(Window);
		ExitButton->Draw(Window);

		break;
	}
}