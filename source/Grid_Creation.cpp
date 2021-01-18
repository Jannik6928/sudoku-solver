# include <vector>

void define_box(int(&grid)[9][9][10]) {
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			if (a < 3) {
				if (b < 3) {
					grid[a][b][9] = 1;
				}
				else if (b < 6) {
					grid[a][b][9] = 2;
				}
				else {
					grid[a][b][9] = 3;
				}
			}
			else if (a < 6) {
				if (b < 3) {
					grid[a][b][9] = 4;
				}
				else if (b < 6) {
					grid[a][b][9] = 5;
				}
				else {
					grid[a][b][9] = 6;
				}
			}
			else {
				if (b < 3) {
					grid[a][b][9] = 7;
				}
				else if (b < 6) {
					grid[a][b][9] = 8;
				}
				else {
					grid[a][b][9] = 9;
				}
			}
		}
	}
}

void create_grid(int(&grid)[9][9][10], std::vector<int> &valid_number, std::vector<int> &valid_row, std::vector<int> &valid_column) {
	define_box(grid);
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			if (grid[a][b][0] == 0) {
				for (int c = 0; c < 9; c++) {
					grid[a][b][c] = c + 1;
				}
			}
			else {
				int temp = grid[a][b][0];
				grid[a][b][0] = 0;
				grid[a][b][temp - 1] = temp;
				valid_row.push_back(a);
				valid_column.push_back(b);
				valid_number.push_back(temp);
			}
		}
	}
}