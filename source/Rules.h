void check_column(int index, std::vector<int> const &valid_number, std::vector<int> const &valid_column, std::vector<int> const &valid_row, int(&grid)[9][9][10]);
void check_row(int index, std::vector <int> const &valid_number, std::vector <int> const &valid_row, std::vector <int> const &valid_column, int(&grid)[9][9][10]);
void single_orth(int(&grid)[9][9][10]);
void single_box(int(&grid)[9][9][10]);
void get_valid(int(&grid)[9][9][10], std::vector <int> &valid_number, std::vector <int> &valid_row, std::vector <int> &valid_column);
bool count_number(std::vector <int> const &vector);
void pointing_set(std::vector <int> &point_row, std::vector <int> &point_col, int(&grid)[9][9][10]);
void visible_row(int row, int col, int(&grid)[9][9][10]);
void visible_col(int row, int col, int(&grid)[9][9][10]);
int get_subarray_length(int row, int col, int(&grid)[9][9][10]);
void visible_box(int row, int col, int(&grid)[9][9][10]);
void visible_pair(int(&grid)[9][9][10]);
void check_box(int index, std::vector<int> const &valid_number, std::vector<int> const &valid_row, std::vector<int> const &valid_column, int(&grid)[9][9][10]);