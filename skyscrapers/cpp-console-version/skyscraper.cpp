#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <chrono> 
using namespace std::chrono;

int N;

struct Field {
public:
	int value;
	std::vector<int> options;

	Field() {
		value = 0;
		for (int i = 1; i <= N; ++i)
			options.push_back(i);
	}
};

struct Command {
public:
	char direction;
	int directionValue;
	int value;

	Command(char direction, int directionValue, int value) {
		this->direction = direction;
		this->directionValue = directionValue;
		this->value = value;
	}
};

Field** grid;
void initializeGrid();
void eraseUseless();
void print();
bool solvable();
bool ready(int& row, int& col);
bool possible(int row, int col, int val);
bool correct();
bool check();
bool legit();
bool isNumber(std::string n);
int getHeight(int dir, bool rev, bool updown);
int getCount(int dir, bool rev, bool updown);
int NPosition(int dir, bool rev, bool updown);
int allOptions(int row, int col);
int hidden(int& row, int& col);
std::vector<Field*> indexes(int row, int col);

std::vector<Command> inputs;

int main()
{
	char dir;
	std::string n;
	std::string loc, val;
	std::cin >> N >> n;
	if (!isNumber(n) || (N < 4 || N > 8) || (std::stoi(n) < 0 || std::stoi(n) > N * 4)) {
		printf("Wrong data!");
		return -1;
	}
	for (int i = 0; i < std::stoi(n); ++i) {
		std::cin >> dir >> loc >> val;
		if (loc.size() > 1 || val.size() > 1 || (toupper(dir) != 'U' && toupper(dir) != 'D' && toupper(dir) != 'L' && toupper(dir) != 'R') || (loc[0] - 48 < 1 || loc[0] - 48 > N) || (val[0] - 48 < 1 || val[0] - 48 > N)) {
			printf("Wrong data!");
			return -1;
		}
		inputs.push_back(Command(toupper(dir), loc[0] - 48, val[0] - 48));
	}
	grid = new Field * [N];
	initializeGrid();
	auto start = high_resolution_clock::now();
	if (!solvable())
		printf("Couldn't find any solution... :[");
	else
		print();
	auto stop = high_resolution_clock::now();
	printf("\ntime: %llu milisec", std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count());

	return 0;
}

bool isNumber(std::string n) {
	return n.size() >= 1 && std::all_of(n.begin(), n.end(), ::isdigit);
}

void initializeGrid() {
	for (int i = 0; i < N; ++i) {
		grid[i] = new Field[N];
		for (int j = 0; j < N; ++j)
			grid[i][j] = Field();
	}
	for (int i = 0; i <= N; ++i)
		eraseUseless();
}

bool solvable() {
	int row = 0, col = 0;

	if (!check() || !legit())
		return false;

	if (ready(row, col))
		return correct();

	int hid = hidden(row, col);
	std::vector<int> copy = grid[row][col].options;

	if (hid != -1) {
		grid[row][col].value = hid;
		grid[row][col].options.clear();
		std::vector<Field*> removable = indexes(row, col);
		for (int i = 0; i < removable.size(); ++i)
			removable[i]->options.erase(std::remove(removable[i]->options.begin(), removable[i]->options.end(), grid[row][col].value), removable[i]->options.end());
		if (solvable())
			return true;
		for (int i = 0; i < removable.size(); ++i)
			removable[i]->options.push_back(grid[row][col].value);
		grid[row][col].value = 0;
	}

	for (int i = 0; i < grid[row][col].options.size(); ++i) {
		std::vector <int> mcopy = grid[row][col].options;
		grid[row][col].value = grid[row][col].options[i];
		grid[row][col].options.clear();
		std::vector<Field*> removable = indexes(row, col);
		for (int j = 0; j < removable.size(); ++j)
			removable[j]->options.erase(std::remove(removable[j]->options.begin(), removable[j]->options.end(), grid[row][col].value), removable[j]->options.end());
		if (solvable())
			return true;
		for (int j = 0; j < removable.size(); ++j)
			removable[j]->options.push_back(grid[row][col].value);
		grid[row][col].options = mcopy;
		grid[row][col].value = 0;
		grid[row][col].options.erase(grid[row][col].options.begin() + i);
		--i;
	}

	grid[row][col].options = copy;
	return false;
}

std::vector<Field*> indexes(int row, int col) {
	std::vector<Field*> result;
	for (int i = 0; i < N; ++i) {
		if (i != row && std::find(grid[i][col].options.begin(), grid[i][col].options.end(), grid[row][col].value) != grid[i][col].options.end())
			result.push_back(&grid[i][col]);
		if (i != col && std::find(grid[row][i].options.begin(), grid[row][i].options.end(), grid[row][col].value) != grid[row][i].options.end())
			result.push_back(&grid[row][i]);
	}
	return result;
}

int hidden(int& row, int& col) {
	for (int a = 0; a < N; ++a)
		for (int b = 0; b < N; ++b) {
			bool horizont = true, vertical = true;

			if (grid[a][b].value != 0)
				for (int c = 0; c < grid[a][b].options.size(); c++) {
					for (int d = 0; d < N; ++d) {
						if (d != b && std::find(grid[a][d].options.begin(), grid[a][d].options.end(), grid[a][b].options[c]) != grid[a][d].options.end())
							horizont = false;
						if (d != a && std::find(grid[d][b].options.begin(), grid[d][b].options.end(), grid[a][b].options[c]) != grid[d][b].options.end())
							vertical = false;
					}
					if (vertical || horizont) {
						row = a;
						col = b;
						return grid[a][b].options[c];
					}
				}
		}
	return -1;
}

bool legit() {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) {
			if (grid[i][j].options.size() == 0 && grid[i][j].value == 0)
				return false;
			for (int k = 0; k < N; ++k)
				if ((j != k && grid[i][j].value == grid[i][k].value && grid[i][k].value != 0) || (i != k && grid[i][j].value == grid[k][j].value && grid[k][j].value != 0))
					return false;
		}
	return true;
}

bool possible(int row, int col, int val) {
	for (int i = 0; i < N; ++i)
		if (grid[i][col].value == val || grid[row][i].value == val)
			return false;
	return true;
}

bool ready(int& row, int& col) {
	int r = -1, c = -1, min = N + 1;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if ((r == -1 && grid[i][j].value == 0) || (grid[i][j].value == 0 && allOptions(i, j) < min)) {
				r = i;
				c = j;
				min = allOptions(i, j);
			}
	row = r;
	col = c;
	return r == -1;
}

int allOptions(int row, int col) {
	int count = 0;
	for (int i = 0; i < grid[row][col].options.size(); ++i)
		if (possible(row, col, grid[row][col].options[i]))
			count++;
	return count;
}

void eraseUseless() {
	int row, col;
	for (auto& inp : inputs) {
		if (inp.value == 1) {
			row = (inp.direction == 'L' || inp.direction == 'R') ? inp.directionValue - 1 : (inp.direction == 'U' ? 0 : N - 1);
			col = (inp.direction == 'U' || inp.direction == 'D') ? inp.directionValue - 1 : (inp.direction == 'L' ? 0 : N - 1);
			grid[row][col].value = N;
			grid[row][col].options.clear();
		}

		for (int i = inp.value - 1, j = 0; i >= 1; --i, ++j) {
			row = (inp.direction == 'L' || inp.direction == 'R') ? inp.directionValue - 1 : (inp.direction == 'D' ? N - 1 - j : j);
			col = (inp.direction == 'U' || inp.direction == 'D') ? inp.directionValue - 1 : (inp.direction == 'R' ? N - 1 - j : j);
			for (int r = N - i + 1; r <= N; ++r)
				grid[row][col].options.erase(std::remove(grid[row][col].options.begin(), grid[row][col].options.end(), r), grid[row][col].options.end());
		}

		int n = NPosition(inp.directionValue, inp.direction == 'D' || inp.direction == 'R', inp.direction == 'D' || inp.direction == 'U');
		if (inp.value == 2 && n != -1 && n != 1) {
			row = (inp.direction == 'L' || inp.direction == 'R') ? inp.directionValue - 1 : (inp.direction == 'U' ? 0 : N - 1);
			col = (inp.direction == 'U' || inp.direction == 'D') ? inp.directionValue - 1 : (inp.direction == 'L' ? 0 : N - 1);
			for (int i = 1; i < n; ++i)
				grid[row][col].options.erase(std::remove(grid[row][col].options.begin(), grid[row][col].options.end(), i), grid[row][col].options.end());

			for (int i = 1; i < n; ++i) {
				row = (inp.direction == 'L' || inp.direction == 'R') ? row : (inp.direction == 'U' ? i : N - 1 - i);
				col = (inp.direction == 'U' || inp.direction == 'D') ? col : (inp.direction == 'L' ? i : N - 1 - i);
				grid[row][col].options.erase(std::remove(grid[row][col].options.begin(), grid[row][col].options.end(), N), grid[row][col].options.end());
			}
		}

		row = (inp.direction == 'L' || inp.direction == 'R') ? inp.directionValue - 1 : (inp.direction == 'D' ? N - 1 - (inp.value - 1) : inp.value - 1);
		col = (inp.direction == 'U' || inp.direction == 'D') ? inp.directionValue - 1 : (inp.direction == 'R' ? N - 1 - (inp.value - 1) : inp.value - 1);
		if (grid[row][col].value == N) {
			for (int i = 1; i < inp.value - 1; ++i) {
				for (int j = N - inp.value; j <= inp.value - 1 - i; ++j) {
					row = (inp.direction == 'L' || inp.direction == 'R') ? row : (inp.direction == 'D' ? N - 1 - (inp.value - 1) + i : inp.value - 1 - i);
					col = (inp.direction == 'U' || inp.direction == 'D') ? col : (inp.direction == 'R' ? N - 1 - (inp.value - 1) + i : inp.value - 1 - i);
					grid[row][col].options.erase(std::remove(grid[row][col].options.begin(), grid[row][col].options.end(), j), grid[row][col].options.end());
				}
			}
		}

		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j) {
				if (grid[i][j].options.size() == 1 && grid[i][j].value == 0) {
					grid[i][j].value = grid[i][j].options[0];
					grid[i][j].options.clear();
				}
				for (int k = 0; k < N; ++k)
					if (grid[i][j].value != 0) {
						grid[i][k].options.erase(std::remove(grid[i][k].options.begin(), grid[i][k].options.end(), grid[i][j].value), grid[i][k].options.end());
						grid[k][j].options.erase(std::remove(grid[k][j].options.begin(), grid[k][j].options.end(), grid[i][j].value), grid[k][j].options.end());
					}
			}

		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				for (int v = 0; v < grid[i][j].options.size(); ++v) {
					bool vertical = true, hortizontal = true;
					for (int k = 0; k < N; ++k) {
						if (grid[i][k].value == grid[i][j].options[v] || (k != j && std::find(grid[i][k].options.begin(), grid[i][k].options.end(), grid[i][j].options[v]) != grid[i][k].options.end()))
							vertical = false;
						if (grid[k][j].value == grid[i][j].options[v] || (k != i && std::find(grid[k][j].options.begin(), grid[k][j].options.end(), grid[i][j].options[v]) != grid[k][j].options.end()))
							hortizontal = false;
					}
					if (vertical || hortizontal) {
						grid[i][j].value = grid[i][j].options[v];
						grid[i][j].options.clear();
						break;
					}
				}
	}
}

bool check() {
	for (int i = 0; i < inputs.size(); ++i) {
		if (getHeight(inputs[i].directionValue, (inputs[i].direction == 'R' || inputs[i].direction == 'D'), (inputs[i].direction == 'D' || inputs[i].direction == 'U')) > inputs[i].value
			&& grid[(inputs[i].direction == 'L' || inputs[i].direction == 'R') ? inputs[i].directionValue - 1 : (inputs[i].direction == 'U' ? 0 : N - 1)][(inputs[i].direction == 'U' || inputs[i].direction == 'D') ? inputs[i].directionValue - 1 : (inputs[i].direction == 'L' ? 0 : N - 1)].value != 0
			&& grid[(inputs[i].direction == 'L' || inputs[i].direction == 'R') ? inputs[i].directionValue - 1 : (inputs[i].direction == 'U' ? 1 : N - 2)][(inputs[i].direction == 'U' || inputs[i].direction == 'D') ? inputs[i].directionValue - 1 : (inputs[i].direction == 'L' ? 1 : N - 2)].value != 0)
			return false;
		if (getCount(inputs[i].directionValue, (inputs[i].direction == 'R' || inputs[i].direction == 'D'), (inputs[i].direction == 'D' || inputs[i].direction == 'U')) == N
			&& getHeight(inputs[i].directionValue, (inputs[i].direction == 'R' || inputs[i].direction == 'D'), (inputs[i].direction == 'D' || inputs[i].direction == 'U')) != inputs[i].value)
			return false;
	}
	return true;
}

bool correct() {
	for (int i = 0; i < inputs.size(); ++i)
		if (getHeight(inputs[i].directionValue, (inputs[i].direction == 'R' || inputs[i].direction == 'D'), (inputs[i].direction == 'D' || inputs[i].direction == 'U')) != inputs[i].value)
			return false;
	return true;
}

int getHeight(int dir, bool rev, bool updown) {
	int count = 0, max = 0;
	for (int j = 0; j < N; ++j) {
		int row = !updown ? dir - 1 : (rev ? N - 1 - j : j);
		int col = updown ? dir - 1 : (rev ? N - 1 - j : j);
		if (grid[row][col].value > max) {
			max = grid[row][col].value;
			count++;
		}
	}
	return count;
}

int getCount(int dir, bool rev, bool updown) {
	int count = 0, max = 0;
	for (int j = 0; j < N; ++j) {
		int row = !updown ? dir - 1 : (rev ? N - 1 - j : j);
		int col = updown ? dir - 1 : (rev ? N - 1 - j : j);
		if (grid[row][col].value != 0)
			count++;
	}
	return count;
}

int NPosition(int dir, bool rev, bool updown) {
	for (int j = 0; j < N; ++j) {
		int row = !updown ? dir - 1 : (rev ? N - 1 - j : j);
		int col = updown ? dir - 1 : (rev ? N - 1 - j : j);
		if (grid[row][col].value == N)
			return j;
	}
	return -1;
}

void print() {
	printf("\n");
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			printf("%i%c", grid[i][j].value, j != N - 1 ? ' ' : '\n');
}
