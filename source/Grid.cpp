#include "Grid.h"

Grid::Grid(int const(&puzzle)[9][9][10])
{
	for (unsigned i = 0; i < 9; i++) {
		for (unsigned j = 0; j < 9; j++) {
			for (unsigned k = 0; k < 10; k++) {
				grid[i][j][k] = puzzle[i][j][k];
			}
		}
	}
}

