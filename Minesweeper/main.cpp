#include "Minesweeper.h"

int	main()
{
	auto* Game{ new Minesweeper };
	Game->MainLoop();
	return 0;
}