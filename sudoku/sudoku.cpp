#include <iostream>

bool rows[9][9]{}, columns[9][9]{}, squares[9][9]{};
int grid[9][9];

bool solve(int row, int col);
bool dataCollector();
void print();

int main()
{
	std::cout << "----- SUDOKU SOLVER -----\n\nInsert 9x9 grid:\n";
	if (!dataCollector())
		return std::cout << "Wrong data!", -1;

	if (solve(0, -1)) // in each function call col value is increased, so -1 will automaticly become 0 (I want to start with 0)
		print();
	else
		std::cout << "Holy shrimp! Your sudoku is unsolvable!";

	return 0;
}

bool solve(int row, int col) {
	if (row == 8 && col == 8)
		return true; // basic case, the grid was done
	if (col == 8) {
		row++; // increase the row value and set column value to 0
		col = 0;
	}
	else
		col++;
	if (grid[row][col] != 0) {
		if (solve(row, col)) // statement for this cells with non-0-value (they're already filled, so going to the loop is useless) and the program has to go to the next cell, by the next function call
			return true;
	}
	else {
		// check all possilble values for cell in [row, col] position in the grid //
		// firstly, check if i-value doesn't occur in that row, column and square //
		// if not, suppose the cell [row, col] has i-value, then flag that the row, the column, the square have already i-value (for the next parts of the checking/simulation) //
		// then call the function again and do the same for the next cells //
		// if sth'll go wrong, it means that one of the previous values were bad-placed and program has to go back to that place and take the next (i+1...9) value //
		for (int i = 1; i <= 9; ++i) {
			if (!rows[row][i - 1] && !columns[col][i - 1] && !squares[(row / 3) * 3 + (col / 3)][i - 1]) {
				grid[row][col] = i;
				rows[row][i - 1] = columns[col][i - 1] = squares[(row / 3) * 3 + (col / 3)][i - 1] = true;
				if (solve(row, col))
					return true;
				grid[row][col] = 0;
				rows[row][i - 1] = columns[col][i - 1] = squares[(row / 3) * 3 + (col / 3)][i - 1] = false;
			}
		}
	}
	return false;
}

// getting an input from user in pretty dangerous way, but still prevents from getting the same values in the same row/column/square //
bool dataCollector() {
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j) {
			std::cin >> grid[i][j];
			if (grid[i][j] > 0) {
				if (rows[i][grid[i][j] - 1] || columns[j][grid[i][j] - 1] || squares[(i / 3) * 3 + (j / 3)][grid[i][j] - 1])
					return false;
				rows[i][grid[i][j] - 1] = columns[j][grid[i][j] - 1] = squares[(i / 3) * 3 + (j / 3)][grid[i][j] - 1] = true;
			}
		}
	return true;
}

// printing the grid //
void print() {
	std::cout << '\n';
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			std::cout << grid[i][j] << (j == 8 ? "\n" : " ");
		}
	}
	std::cout << '\n';
}
