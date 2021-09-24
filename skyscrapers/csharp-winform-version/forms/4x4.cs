using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Windows.Forms;

namespace skyscraperapp {
    public partial class _4x4 : UserControl, Solvable {
        List<Solver.Skyscraper.Command> commands;
        TextBox[,] fields;
        TextBox[] comm;
        public _4x4() {
            InitializeComponent();
            commands = new List<Solver.Skyscraper.Command>();
            fields = new TextBox[,] {
                {field1, field2, field3, field4 },
                {field5, field6, field7, field8 },
                {field9, field10, field11, field12 },
                {field13, field14, field15, field16 }
            };

            comm = new TextBox[] {
                u1, u2, u3, u4,
                r1, r2, r3, r4,
                d1, d2, d3, d4,
                l1, l2, l3, l4
            };
        }

        private void textChanged(object sender, EventArgs e) {
            if ((sender as TextBox).Text.Length > 0 && ((sender as TextBox).Text[0] < 49 || (sender as TextBox).Text[0] > 52)) {
                (sender as TextBox).Text = "";
                return;
            }
            commands.Clear();
            foreach (var tb in comm)
                if (!commands.Any(x => x.dir == tb.Name[0] - 32 && x.loc == tb.Name[1] - 48) && tb.Text.Length > 0)
                    commands.Add(new Solver.Skyscraper.Command(Convert.ToChar(tb.Name[0] - 32), tb.Name[1]-48, tb.Text[0]-48));
        }

        public void Clear(object sender, EventArgs e) {
            commands.Clear();
            foreach (var tb in fields)
                tb.Text = "";
            foreach (var c in comm)
                c.Text = "";
        }

        public void Solve(object sender, EventArgs e) {
            Solver.Skyscraper skyscraper = new Solver.Skyscraper(4, commands.ToArray());
            if (skyscraper.Solvable())
                for (int i = 0; i < 4; ++i)
                    for (int j = 0; j < 4; ++j)
                        fields[i, j].Text = skyscraper.GetGrid()[i, j].value.ToString();
            else
                MessageBox.Show("Couldn't find any solution... :[");
        }
    }
}
