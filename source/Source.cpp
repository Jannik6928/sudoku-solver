#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>
#include "IO.h"
#include "Rules.h"
#include "Grid_Creation.h"
#include "Divide.h"
#include "Grid.h"

// WORK ON: make divide() have more depth

std::vector <int> valid_column;
std::vector <int> valid_row;
std::vector <int> valid_number;

std::vector <int> point_row;
std::vector <int> point_col;

std::vector <int> low_row;
std::vector <int> low_col;

void apply_rule(int(&board)[9][9][10]);

void find_low(int(&grid)[9][9][10]);
void copy_grid();
void divide();

std::vector <Grid> gridv;

int counter = 0;

int grid[9][9][10] = {
		{{0},{0},{0},{0},{0},{0},{0},{4},{0}},
		{{0},{3},{0},{0},{0},{0},{0},{0},{8}},
		{{4},{0},{2},{7},{3},{0},{0},{0},{6}},
		{{0},{1},{6},{0},{9},{0},{4},{0},{0}},
		{{0},{0},{0},{0},{1},{0},{0},{0},{0}},
		{{0},{0},{3},{0},{2},{0},{5},{6},{0}},
		{{5},{0},{0},{0},{6},{9},{2},{0},{3}},
		{{3},{0},{0},{0},{0},{0},{0},{7},{0}},
		{{0},{8},{0},{0},{0},{0},{0},{0},{0}}
};


int copy[9][9][10];

int main() {
	std::clock_t start;
	double duration;
	start = std::clock();
	create_grid(grid, valid_number, valid_row, valid_column);

	apply_rule(grid);

	if (valid_row.size() < 81) {
		find_low(grid);
		divide();
	}

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	control_output(grid, duration, valid_row, counter);
	control_output(copy, duration, valid_row, counter);

	int num;
	std::cin >> num;

	return 0;
}

void apply_rule(int(&board)[9][9][10]) {
	unsigned prev_size = 0;
	prev_size = 0;
	while (valid_row.size() != 81 && prev_size != valid_row.size()) {
		prev_size = valid_number.size();
		for (unsigned a = 0; a < valid_number.size(); a++) {
			check_row(a, valid_number, valid_row, valid_column, board);
			check_column(a, valid_number, valid_column, valid_row, board);
			check_box(a, valid_number, valid_row, valid_column, board);
		}
		single_orth(board);
		single_box(board);

		visible_pair(board);
		pointing_set(point_row, point_col, board);

		get_valid(board, valid_number, valid_row, valid_column);
		counter++;
	}
}

void find_low(int(&grid)[9][9][10]) {
	for (int l = 2; l < 10; l++) {
		bool flag = false;
		for (int a = 0; a < 9; a++) {
			for (int b = 0; b < 9; b++) {
				if (get_subarray_length(a, b, grid) == l) {
					flag = true;
					low_row.push_back(a);
					low_col.push_back(b);
				}
			}
		}
		if (flag == true) {
			break;
		}
	}
}

void copy_grid() {
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			for (int c = 0; c < 10; c++) {
				copy[a][b][c] = grid[a][b][c];
			}
		}
	}
}

// only able to go 1 layer deep
void divide() {
	copy_grid();
	for (unsigned i = 0; i < low_row.size(); i++) {
		for (int a = 0; a < 9; a++) {
			if (copy[low_row[i]][low_col[i]][a] != 0) {
				for (int b = 0; b < 9; b++) {
					if (b != a) {
						copy[low_row[i]][low_col[i]][b] = 0;
					}
				}

				valid_row.clear();
				valid_column.clear();
				valid_number.clear();

				get_valid(copy, valid_number, valid_row, valid_column);

				apply_rule(copy);

				if (valid_row.size() == 81) {
					break;
				}

			}
			copy_grid();
		}
		if (valid_row.size() == 81) {
			break;
		}
	}
}