using System;
using System.Windows.Forms;

namespace skyscraperapp {
    public partial class Main : Form {
        UserControl[] boards;

        public Main() {
            InitializeComponent();
            boards = new UserControl[] { _4x41, _5x51, _6x61, _7x71, _8x81 };
        }

        private void size_ValueChanged(object sender, EventArgs e) {
            foreach (var b in boards) {
                if (b.Name[1] == size.Value + 48)
                    b.Visible = true;
                else {
                    b.Visible = false;
                    (b as Solvable).Clear(this, e);
                }
            }
        }

        private void solve(object sender, EventArgs e) {
            foreach (var b in boards)
                if (b.Visible)
                    (b as Solvable).Solve(this, e);
        }

        private void clear(object sender, EventArgs e) {
            foreach (var b in boards)
                if (b.Visible)
                    (b as Solvable).Clear(this, e);
        }
    }
}
