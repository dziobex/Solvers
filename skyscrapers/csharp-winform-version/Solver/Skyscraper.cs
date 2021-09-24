using System;
using System.Collections.Generic;

namespace skyscraperapp.Solver
{
    class Skyscraper
    {
        Command[] inputs;
        Field[,] grid;
        int N;

        public Skyscraper(int N, Command[] inputs)
        {
            this.N = N;
            this.inputs = inputs;
            grid = new Field[N, N];
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    grid[i, j] = new Field(N);
            for (int i = 0; i <= N; ++i)
                eraseUseless();
        }

        public bool Solvable()
        {
            int row = 0, col = 0;

            if (!way() || !check() || !legit()) {
                return false;
            }

            int r = -1, c = -1, min = N + 1;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    if ((r == -1 && grid[i, j].value == 0) || (grid[i, j].value == 0 && allOptions(i, j) < min)) {
                        r = i;
                        c = j;
                        min = allOptions(i, j);
                    }
            row = r;
            col = c;
            bool ready = r == -1;

            if (ready)
                return correct();

            int hid = 0;
            bool contin = true;
            for (int a = 0; (a < N && contin); ++a)
                for (int b = 0; (b < N && contin); ++b) {
                    bool horizont = true, vertical = true;

                    if (grid[a, b].value != 0)
                        for (int cc = 0; (cc < grid[a, b].options.Count && contin); cc ++) {
                            for (int d = 0; d < N; ++d) {
                                if (d != b && grid[a, d].options.Contains( grid[a, b].options[cc]))
                                    horizont = false;
                                if (d != a && grid[d, b].options.Contains(grid[a, b].options[cc]))
                                    vertical = false;
                            }
                            if (vertical || horizont) {
                                row = a;
                                col = b;
                                contin = false;
                                hid = grid[a, b].options[cc];
                                break;
                            }
                        }
                }

            List<int> bcopy = new List<int>(grid[row, col].options);
            if (!contin) {
                grid[row, col].value = hid;
                grid[row, col].options.Clear();
                List<Tuple<int, int>> removable = indexes(row, col);
                for (int j = 0; j < removable.Count; ++j)
                    grid[removable[j].Item1, removable[j].Item2].options.RemoveAll(x => x == grid[row, col].value);
                if (Solvable())
                    return true;
                for (int j = 0; j < removable.Count; ++j)
                    grid[removable[j].Item1, removable[j].Item2].options.Add(grid[row, col].value);
                grid[row, col].value = 0;
            }

            for (int i = 0; i < grid[row, col].options.Count; ++i) {
                List<int> mcopy = new List<int>(grid[row, col].options);
                grid[row, col].value = grid[row, col].options[i];
                grid[row, col].options.Clear();
                List<Tuple<int, int>> removable = indexes(row, col);
                for (int j = 0; j < removable.Count; ++j)
                    grid[removable[j].Item1, removable[j].Item2].options.RemoveAll(x => x == grid[row, col].value);
                if (Solvable())
                    return true;
                for (int j = 0; j < removable.Count; ++j)
                    grid[removable[j].Item1, removable[j].Item2].options.Add(grid[row, col].value);
                grid[row, col].options = new List<int>(mcopy);
                grid[row, col].value = 0;
            }
            grid[row, col].options = bcopy;

            return false;
        }

        List<Tuple<int, int>> indexes(int row, int col) {
            List<Tuple<int, int>> result = new List<Tuple<int, int>>();
            for (int i = 0; i < N; ++i) {
                if (i != row && grid[i, col].options.Contains(grid[row, col].value))
                    result.Add(Tuple.Create(i, col));
                if (i != col && grid[row, i].options.Contains(grid[row, col].value))
                    result.Add(Tuple.Create(row, i));
            }
            return result;
        }

        bool check() {
            for (int i = 0; i < inputs.Length; ++i)
                if (getHeight(inputs[i].loc, (inputs[i].dir == 'R' || inputs[i].dir == 'D'), (inputs[i].dir == 'D' || inputs[i].dir == 'U')) > inputs[i].val
                    && grid[(inputs[i].dir == 'L' || inputs[i].dir == 'R') ? inputs[i].loc - 1 : (inputs[i].dir == 'U' ? 0 : N - 1), (inputs[i].dir == 'U' || inputs[i].dir == 'D') ? inputs[i].loc - 1 : (inputs[i].dir == 'L' ? 0 : N - 1)].value != 0
                    && grid[(inputs[i].dir == 'L' || inputs[i].dir == 'R') ? inputs[i].loc - 1 : (inputs[i].dir == 'U' ? 1 : N - 2), (inputs[i].dir == 'U' || inputs[i].dir == 'D') ? inputs[i].loc - 1 : (inputs[i].dir == 'L' ? 1 : N - 2)].value != 0)
                    return false;
            return true;
        }

        bool way() {
            for (int a = 0; a < inputs.Length; ++a)
                if (getCount(inputs[a].loc, (inputs[a].dir == 'R' || inputs[a].dir == 'D'), (inputs[a].dir == 'D' || inputs[a].dir == 'U')) == N
                    && getHeight(inputs[a].loc, (inputs[a].dir == 'R' || inputs[a].dir == 'D'), (inputs[a].dir == 'D' || inputs[a].dir == 'U')) != inputs[a].val)
                    return false;
            return true;
        }

        int getCount(int dir, bool rev, bool updown) {
            int count = 0;
            for (int j = 0; j < N; ++j) {
                int row = !updown ? dir - 1 : (rev ? N - 1 - j : j);
                int col = updown ? dir - 1 : (rev ? N - 1 - j : j);
                if (grid[row, col].value != 0)
                    count++;
            }
            return count;
        }

        bool legit() {
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    for (int k = 0; k < N; ++k)
                        if ((j != k && grid[i, j].value == grid[i, k].value && grid[i, k].value != 0) || (i != k && grid[i, j].value == grid[k, j].value && grid[k, j].value != 0))
                            return false;
            return true;
        }

        int allOptions(int row, int col) {
            int count = 0;
            for (int i = 0; i < grid[row, col].options.Count; ++i)
                if (possible(row, col, grid[row, col].options[i]))
                    count++;
            return count;
        }

        bool correct()
        {
            for (int i = 0; i < inputs.Length; ++i)
                if (getHeight(inputs[i].loc, (inputs[i].dir == 'R' || inputs[i].dir == 'D'), (inputs[i].dir == 'D' || inputs[i].dir == 'U')) != inputs[i].val)
                    return false;
            return true;
        }

        void eraseUseless() {
            int row, col;
            foreach (var inp in inputs) {
                if (inp.val == 1) {
                    row = (inp.dir == 'L' || inp.dir == 'R') ? inp.loc - 1 : (inp.dir == 'U' ? 0 : N - 1);
                    col = (inp.dir == 'U' || inp.dir == 'D') ? inp.loc - 1 : (inp.dir == 'L' ? 0 : N - 1);
                    grid[row, col].value = N;
                    grid[row, col].options.Clear();
                }

                for (int i = inp.val - 1, j = 0; i >= 1; --i, ++j) {
                    row = (inp.dir == 'L' || inp.dir == 'R') ? inp.loc - 1 : (inp.dir == 'D' ? N - 1 - j : j);
                    col = (inp.dir == 'U' || inp.dir == 'D') ? inp.loc - 1 : (inp.dir == 'R' ? N - 1 - j : j);
                    for (int r = N - i + 1; r <= N; ++r)
                        grid[row, col].options.Remove(r);
                }

                int n = NPosition(inp.loc, inp.dir == 'D' || inp.dir == 'R', inp.dir == 'D' || inp.dir == 'U');
                if (inp.val == 2 && n != -1 && n != 1) {
                    row = (inp.dir == 'L' || inp.dir == 'R') ? inp.loc - 1 : (inp.dir == 'U' ? 0 : N - 1);
                    col = (inp.dir == 'U' || inp.dir == 'D') ? inp.loc - 1 : (inp.dir == 'L' ? 0 : N - 1);
                    for (int i = 1; i < n; ++i)
                        grid[row, col].options.Remove(i);

                    for (int i = 1; i < n; ++i) {
                        row = (inp.dir == 'L' || inp.dir == 'R') ? row : (inp.dir == 'U' ? i : N - 1 - i);
                        col = (inp.dir == 'U' || inp.dir == 'D') ? col : (inp.dir == 'L' ? i : N - 1 - i);
                        grid[row, col].options.Remove(N);
                    }
                }

                row = (inp.dir == 'L' || inp.dir == 'R') ? inp.loc - 1 : (inp.dir == 'D' ? N - 1 - (inp.val - 1) : inp.val - 1);
                col = (inp.dir == 'U' || inp.dir == 'D') ? inp.loc - 1 : (inp.dir == 'R' ? N - 1 - (inp.val - 1) : inp.val - 1);
                if (grid[row, col].value == N) {
                    for (int i = 1; i < inp.val - 1; ++i) {
                        for (int j = N - inp.val; j <= inp.val - 1 - i; ++j) {
                            row = (inp.dir == 'L' || inp.dir == 'R') ? row : (inp.dir == 'D' ? N - 1 - (inp.val - 1) + i : inp.val - 1 - i);
                            col = (inp.dir == 'U' || inp.dir == 'D') ? col : (inp.dir == 'R' ? N - 1 - (inp.val - 1) + i : inp.val - 1 - i);
                            grid[row, col].options.Remove(j);
                        }
                    }
                }

                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < N; ++j) {
                        if (grid[i, j].options.Count == 1 && grid[i, j].value == 0) {
                            grid[i, j].value = grid[i, j].options[0];
                            grid[i, j].options.Clear();
                        }
                        for (int k = 0; k < N; ++k)
                            if (grid[i, j].value != 0) {
                                grid[i, k].options.Remove(grid[i, j].value);
                                grid[k, j].options.Remove(grid[i, j].value);
                            }
                    }

                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < N; ++j)
                        for (int v = 0; v < grid[i, j].options.Count; ++v) {
                            bool vertical = true, hortizontal = true;
                            for (int k = 0; k < N; ++k) {
                                if (grid[i, k].value == grid[i, j].options[v] || (k != j && grid[i, k].options.Contains(grid[i, j].options[v])))
                                    vertical = false;
                                if (grid[k, j].value == grid[i, j].options[v] || (k != i && grid[k, j].options.Contains(grid[i, j].options[v])))
                                    hortizontal = false;
                            }
                            if (vertical || hortizontal) {
                                grid[i, j].value = grid[i, j].options[v];
                                grid[i, j].options.Clear();
                                break;
                            }
                        }
            }
        }

        int NPosition(int dir, bool rev, bool updown) {
            for (int j = 0; j < N; ++j) {
                int row = !updown ? dir - 1 : (rev ? N - 1 - j : j);
                int col = updown ? dir - 1 : (rev ? N - 1 - j : j);
                if (grid[row, col].value == N)
                    return j;
            }
            return -1;
        }

        int getHeight(int dir, bool rev, bool updown) {
            int count = 0, max = 0;
            for (int j = 0; j < N; ++j) {
                int row = !updown ? dir - 1 : (rev ? N - 1 - j : j);
                int col = updown ? dir - 1 : (rev ? N - 1 - j : j);
                if (grid[row, col].value > max) {
                    max = grid[row, col].value;
                    count++;
                }
            }
            return count;
        }

        bool possible(int row, int col, int n) {
            for (int i = 0; i < N; ++i)
                if (grid[i, col].value == n || grid[row, i].value == n)
                    return false;
            return true;
        }

        public Field[,] GetGrid() => grid;

        internal struct Field {
            public int value;
            public List<int> options;

            public Field(int size) {
                value = 0;
                options = new List<int>();
                for (int i = 1; i <= size; ++i)
                    options.Add(i);
            }
        }

        public struct Command {
            public char dir;
            public int loc;
            public int val;
            public Command(char dir, int loc, int val) {
                this.dir = dir;
                this.loc = loc;
                this.val = val;
            }
        }
    }
}
