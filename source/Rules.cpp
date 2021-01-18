#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdio>

void check_column(int index, std::vector<int> const &valid_number, std::vector<int> const &valid_column, std::vector<int> const &valid_row, int(&grid)[9][9][10]) {
	for (int a = 0; a < 9; a++) {
		if (grid[a][valid_column[index]][valid_number[index] - 1] == valid_number[index] && valid_row[index] != a) {
			(grid[a][valid_column[index]][valid_number[index] - 1] = 0);
		}
	}
}

void check_row(int index, std::vector <int> const &valid_number, std::vector <int> const &valid_row, std::vector <int> const &valid_column, int(&grid)[9][9][10]) {
	for (int a = 0; a < 9; a++) {
		if (grid[valid_row[index]][a][valid_number[index] - 1] == valid_number[index] && valid_column[index] != a) {
			grid[valid_row[index]][a][valid_number[index] - 1] = 0;
		}
	}
}

void single_orth(int(&grid)[9][9][10]) {
	for (int n = 1; n < 10; n++) {
		for (int a = 0; a < 9; a++) {
			int row_counter = 0;
			int row_temp1;
			int col_counter = 0;
			int col_temp1;
			for (int b = 0; b < 9; b++) {
				if (grid[a][b][n - 1] == n) {
					row_temp1 = b;
					row_counter++;
				}
				if (grid[b][a][n - 1] == n) {
					col_temp1 = b;
					col_counter++;
				}
			}
			if (row_counter == 1) {
				for (int d = 0; d < 9; d++) {
					grid[a][row_temp1][d] = 0;
				}
				grid[a][row_temp1][n - 1] = n;
			}
			if (col_counter == 1) {
				for (int e = 0; e < 9; e++) {
					grid[col_temp1][a][e] = 0;
				}
				grid[col_temp1][a][n - 1] = n;
			}
		}
	}
}

void get_valid(int(&grid)[9][9][10], std::vector <int> &valid_number, std::vector <int> &valid_row, std::vector <int> &valid_column) {
	valid_row.clear();
	valid_column.clear();
	valid_number.clear();
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			int temp;
			int counter = 0;
			for (int c = 0; c < 9; c++) {
				if (grid[a][b][c] != 0) {
					temp = grid[a][b][c];
					counter++;
				}
			}
			if (counter == 1) {
				valid_row.push_back(a);
				valid_column.push_back(b);
				valid_number.push_back(temp);
			}
		}
	}
}

bool count_number(std::vector <int> const &vector) {
	bool all_same = true;
	for (unsigned a = 1; a < vector.size(); a++) {
		if (vector[a] != vector[0]) {
			all_same = false;
			break;
		}
	}
	return all_same;
}

void pointing_set(std::vector <int> &point_row, std::vector <int> &point_col, int(&grid)[9][9][10]) {
	for (int row = 0; row < 9; row += 3) {
		for (int col = 0; col < 9; col += 3) {
			for (int num = 0; num < 9; num++) {
				int counter = 0;
				point_row.clear();
				point_col.clear();
				for (int a = row; a < row + 3; a++) {
					for (int b = col; b < col + 3; b++) {
						if (grid[a][b][num - 1] == num) {
							counter++;
							point_row.push_back(a);
							point_col.push_back(b);
						}
					}
				}
				if (counter == 2 || counter == 3) {
					if (count_number(point_row) == true) {
						for (int a = 0; a < 9; a++) {
							if (grid[point_row[0]][a][num - 1] == num && grid[point_row[0]][a][9] != grid[point_row[0]][point_col[0]][9]) {
								grid[point_row[0]][a][num - 1] = 0;
							}
						}
					}
					if (count_number(point_col) == true) {
						for (int a = 0; a < 9; a++) {
							if (grid[a][point_col[0]][num - 1] == num && grid[a][point_col[0]][9] != grid[point_row[0]][point_col[0]][9]) {
								grid[a][point_col[0]][num - 1] = 0;
							}
						}
					}
				}
			}
		}
	}
}

void single_box(int(&grid)[9][9][10]) {
	for (int a = 0; a < 9; a += 3) {
		for (int b = 0; b < 9; b += 3) {
			for (int n = 1; n < 10; n++) {
				int counter = 0;
				int row_temp;
				int col_temp;
				for (int row = a; row < a + 3; row++) {
					for (int col = b; col < b + 3; col++) {
						if (grid[row][col][n - 1] == n) {
							row_temp = row;
							col_temp = col;
							counter++;
						}
					}
				}
				if (counter == 1) {
					for (int i = 0; i < 9; i++) {
						grid[row_temp][col_temp][i] = 0;
					}
					grid[row_temp][col_temp][n - 1] = n;
				}
			}
		}
	}
}

void visible_row(int row, int col, int(&grid)[9][9][10]) {
	for (int a = 0; a < 9; a++) {
		int correct = 0;
		for (int c = 0; c < 9; c++) {
			if (grid[row][col][c] == grid[row][a][c] && col != a) {
				correct++;
			}
		}
		if (correct == 9) {
			for (int d = 0; d < 9; d++) {
				for (int e = 0; e < 9; e++) {
					if (grid[row][d][e] == grid[row][col][e] && d != col && d != a) {
						grid[row][d][e] = 0;
					}
				}
			}
			break;
		}
	}
}

void visible_col(int row, int col, int(&grid)[9][9][10]) {
	for (int a = 0; a < 9; a++) {
		int correct = 0;
		for (int b = 0; b < 9; b++) {
			if (grid[row][col][b] == grid[a][col][b] && row != a) {
				correct++;
			}
		}
		if (correct == 9) {
			for (int c = 0; c < 9; c++) {
				for (int d = 0; d < 9; d++) {
					if (grid[row][col][d] == grid[c][col][d] && c != row && c != a) {
						grid[c][col][d] = 0;
					}
				}
			}
			break;
		}
	}
}

int get_subarray_length(int row, int col, int(&grid)[9][9][10]) {
	int possibilities = 0;
	for (int c = 0; c < 9; c++) {
		if (grid[row][col][c] != 0) {
			possibilities++;
		}
	}
	return possibilities;
}

void visible_box(int row, int col, int(&grid)[9][9][10]) {
	for (int a = (int)floor(row / 3) * 3; a < (int)floor(row / 3) * 3 + 3; a++) {
		for (int b = (int)floor(col / 3) * 3; b < (int)floor(col / 3) * 3 + 3; b++) {
			int count = 0;
			for (int n = 0; n < 9; n++) {
				if (grid[a][b][n] == grid[row][col][n] && !(a == row && b == col)) {
					count++;
				}
			}
			if (count == 9) {
				for (int c = (int)floor(row / 3) * 3; c < (int)floor(row / 3) * 3 + 3; c++) {
					for (int d = (int)floor(col / 3) * 3; d < (int)floor(col / 3) * 3 + 3; d++) {
						for (int e = 0; e < 9; e++) {
							if (grid[c][d][e] == grid[row][col][e] && !(c == row && d == col) && !(c == a && d == b)) {
								grid[c][d][e] = 0;
							}
						}
					}
				}
			}
		}
	}
}

void visible_pair(int(&grid)[9][9][10]) {
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			if (get_subarray_length(a, b, grid) == 2) {
				visible_row(a, b, grid);
				visible_col(a, b, grid);
				visible_box(a, b, grid);
			}
		}
	}
}

void check_box(int index, std::vector<int> const &valid_number, std::vector<int> const &valid_row, std::vector<int> const &valid_column, int(&grid)[9][9][10]) {
	for (int a = (int)floor(valid_row[index] / 3) * 3; a < (int)floor(valid_row[index] / 3) * 3 + 3; a++) {
		for (int b = (int)floor(valid_column[index] / 3) * 3; b < (int)floor(valid_column[index] / 3) * 3 + 3; b++) {
			if (grid[a][b][valid_number[index] - 1] == valid_number[index] && a != valid_row[index]) {
				grid[a][b][valid_number[index] - 1] = 0;
			}
		}
	}
}