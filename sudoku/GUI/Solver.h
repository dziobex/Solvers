#pragma once
#include <iostream>

class Solver
{
	bool rows[9][9]{}, columns[9][9]{}, squares[9][9]{}, solvable;
	long long steps = 0;
public:
	int grid[9][9]{};

	Solver() = default;
	bool Initialize(int grid[9][9]);
	bool Solve(int row, int col);

	long long GetSteps() { return steps; }
};