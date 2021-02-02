#include "Minesweeper.h"

int	main()
{
	Minesweeper* Program{ new Minesweeper() };
	Program->MainLoop();
	return 0;
}