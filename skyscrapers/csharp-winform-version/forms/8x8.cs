using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace skyscraperapp {
    public partial class _8x8 : UserControl, Solvable {
        List<Solver.Skyscraper.Command> commands;
        TextBox[,] fields;
        TextBox[] comm;

        public _8x8() {
            InitializeComponent();

            commands = new List<Solver.Skyscraper.Command>();
            fields = new TextBox[,] {
                {field1, field2, field3, field4, field5, field6, field7, field8 },
                {field9, field10, field11, field12, field13, field14, field15, field16 },
                {field17, field18, field19, field20, field21, field22, field23, field24 },
                {field25, field26, field27, field28, field29, field30, field31, field32 },
                {field33, field34, field35, field36, field37, field38, field39, field40 },
                {field41, field42, field43, field44, field45, field46, field47, field48 },
                {field49, field50, field51, field52, field53, field54, field55, field56 },
                {field57, field58, field59, field60, field61, field62, field63, field64 }
            };

            comm = new TextBox[] {
                u1, u2, u3, u4, u5, u6, u7, u8,
                r1, r2, r3, r4, r5, r6, r7, r8,
                d1, d2, d3, d4, d5, d6, d7, d8,
                l1, l2, l3, l4, l5, l6, l7, l8
            };
        }

        private void textChanged(object sender, EventArgs e) {
            if ((sender as TextBox).Text.Length > 0 && ((sender as TextBox).Text[0] < 49 || (sender as TextBox).Text[0] > 56)) {
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
            Solver.Skyscraper skyscraper = new Solver.Skyscraper(8, commands.ToArray());
            if (skyscraper.Solvable())
                for (int i = 0; i < 8; ++i)
                    for (int j = 0; j < 8; ++j)
                        fields[i, j].Text = skyscraper.GetGrid()[i, j].value.ToString();
            else
                MessageBox.Show("Couldn't find any solution... :[");
        }
    }
}
