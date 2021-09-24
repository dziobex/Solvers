using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace skyscraperapp {
    public partial class _6x6 : UserControl, Solvable {
        List<Solver.Skyscraper.Command> commands;
        TextBox[,] fields;
        TextBox[] comm;

        public _6x6() {
            InitializeComponent();
            commands = new List<Solver.Skyscraper.Command>();
            fields = new TextBox[,] {
                {field1, field2, field3, field4, field5, field6 },
                {field7, field8, field9, field10, field11, field12 },
                {field13, field14, field15, field16, field17, field18 },
                {field19, field20, field21, field22, field23, field24 },
                {field25, field26, field27, field28, field29, field30 },
                {field31, field32, field33, field34, field35, field36 }
            };

            comm = new TextBox[] {
                u1, u2, u3, u4, u5, u6,
                r1, r2, r3, r4, r5, r6,
                d1, d2, d3, d4, d5, d6,
                l1, l2, l3, l4, l5, l6
            };
        }

        private void textChanged(object sender, EventArgs e) {
            if ((sender as TextBox).Text.Length > 0 && ((sender as TextBox).Text[0] < 49 || (sender as TextBox).Text[0] > 54)) {
                (sender as TextBox).Text = "";
                return;
            }
            commands.Clear();
            foreach (var tb in comm)
                if (!commands.Any(x => x.dir == tb.Name[0] - 32 && x.loc == tb.Name[1] - 48) && tb.Text.Length > 0)
                    commands.Add(new Solver.Skyscraper.Command(Convert.ToChar(tb.Name[0] - 32), tb.Name[1] - 48, tb.Text[0] - 48));
        }

        public void Clear(object sender, EventArgs e) {
            commands.Clear();
            foreach (var tb in fields)
                tb.Text = "";
            foreach (var c in comm)
                c.Text = "";
        }

        public void Solve(object sender, EventArgs e) {
            Solver.Skyscraper skyscraper = new Solver.Skyscraper(6, commands.ToArray());
            if (skyscraper.Solvable())
                for (int i = 0; i < 6; ++i)
                    for (int j = 0; j < 6; ++j)
                        fields[i, j].Text = skyscraper.GetGrid()[i, j].value.ToString();
            else
                MessageBox.Show("Couldn't find any solution... :[");
        }
    }
}
