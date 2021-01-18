#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>

void print_grid(int(&grid)[9][9][10]) {
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			for (int c = 0; c < 9; c++) {
				if (grid[a][b][c] != 0) {
					std::cout << grid[a][b][c];
				}
				if (c == 8 && b != 8) {
					std::cout << " ";
				}
			}
			if (b == 2 || b == 5) {
				std::cout << "| ";
			}
		}
		std::cout << std::endl;
		if (a == 2 || a == 5) {
			std::cout << "---------------------" << std::endl;
		}
	}
}

int get_length(int(&grid)[9][9][10]) {
	int grid_length = 0;
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			for (int c = 0; c < 9; c++) {
				if (grid[a][b][c] != 0) {
					grid_length++;
				}
			}
		}
	}
	return grid_length;
}

void control_output(int(&grid)[9][9][10], double duration, std::vector <int> &valid_number, int counter) {
	int total_length = get_length(grid);

	if (total_length < 81) {
		std::cout << std::endl << "input is possibly incorrect" << std::endl;
		print_grid(grid);
	}
	else if (total_length > 81) {
		std::cout << std::endl << "unable to solve" << std::endl << std::endl;
		print_grid(grid);
		std::cout << std::endl;
	}
	else {
		print_grid(grid);
		std::cout << std::endl << "Solved in " << duration << " seconds by James' computer!" << std::endl;
		std::cout << "cycles: " << counter << std::endl;
	}
}